
#include <stdexcept>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ai_model.h"
ai_model::ai_model(const std::string &name, matrix *& in, matrix *& out,const vector<string> &sizes
                   ) : name(name), out(out) , in(in),mat(new math("tanh")){

    embed=new matrix("emb", sizes,-1.0 , 1.0);
    if(embed->dimension()<3)throw  std::runtime_error("CUK");
}

ai_model::~ai_model() {
    //in and out created on Models_Matrices
    delete embed;
    delete mat;
    for (auto & it : layers) {
        delete it;
    }
    for (auto & it :weights) {
        delete it;
    }
    for (auto & it : bias) {
        delete it;
    }
}

string ai_model::predict(vector<string> & ins){
    int size = stoi(in->get_shape()[0]);//in matrix 2D matrix
    int row = in->totalsize() / size;

    int embed_element_size=embed->totalsize()/stoi(embed->get_shape()[0]);//size of an element in embedding matrix

    vector<double> in_v;
    for (int i = 0; i < mini_batch; ++i) {
        for (int j = 0; j < row; ++j) {
            int ind = stoi(ins[j]);
            for (int k = 0; k < embed_element_size; ++k) {
                in_v.push_back(embed->_get(ind*embed_element_size+k));
            }
        }
    }
    layers[0]->assign(in_v);

    for (int i = 1; i < layers.size(); ++i) {
        layers[i]->assign(mat->out(weights[i-1], layers[i-1],bias[i-1] , nullptr));
    }

    double min_loss = INT_MAX;
    int index;


    for (int j = 0; j < stoi(embed->get_shape()[0]); ++j) {
        double lss = 0;

        for (int i = 0; i < mini_batch; ++i) {

            vector<double> em;
            for (int k = 0; k < embed_element_size; ++k) {
                em.push_back(embed->_get(j*embed_element_size+k));
            }
            vector<double> ou;

            for (int j = 0; j < embed_element_size; ++j) {
                ou.push_back(layers[layers.size()-1]->_get(embed_element_size*i+j));
            }
            lss = mat->loss(ou , em);
            if(lss < min_loss){
                min_loss=lss;
                index = j;
            }
        }


    }
    cout<<index<<" ";
    return to_string(index);
}

double ai_model::ai_train(const string &func_type,const std::string &mini_batch){
    if (!embed)throw  std::runtime_error("CUK");
    try {
        this->mini_batch = std::stoi(mini_batch);
        create_start_end_layers();
        create_weights_and_biases();
        deal_with_devil();
        return _loss();
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid number format: ");
    } catch (const std::out_of_range& e) {
        throw std::out_of_range("Index out of bounds: " );
    }
}
double ai_model::_loss(){
    return loss;
}
int ai_model::calculate_model_size(){
    int total_size=0;
    total_size+=in->totalsize();
    total_size+=out->totalsize();
    for (int i = 0; i < layers.size(); ++i) {
        total_size+=layers[i]->totalsize();
    }
    return total_size;
}
void ai_model::deal_with_devil(){

    double prev_loss = INT_MAX;
    double avarage_loss = 0.0;
    for (int i = 0; i < 100000; ++i) { // Limit value for stop training
        a_step_ahead();
        avarage_loss+= loss/ 1000;

        if((i-1)%1000==0){
            cout<<avarage_loss<<" ";

            if(prev_loss - avarage_loss > -0.00000001 && prev_loss - avarage_loss < 0.00000001)break; // Converge Point

            prev_loss = avarage_loss;
            avarage_loss = 0.0;
        }
    }
    loss = avarage_loss;
}

void ai_model::a_step_ahead(){
    take_random();
    for (int i = 1; i < layers.size()-1; ++i) {
        layers[i]->assign(mat->out(weights[i-1], layers[i-1],bias[i-1] , nullptr));
    }
    vector<double> changed_matrix;
    for (int i = layers.size()-1; i > 0; --i) {
        changed_matrix=mat->gradient_calculation(weights[i-1], layers[i-1],bias[i-1], layers[i], 0.01); // Gradient descent and out values
        if(i!= layers.size()-1){ // Last layer for target value
            layers[i]->assign(changed_matrix);
        }else{ // Calculate loss with target value
            loss = mat->loss(changed_matrix , layers[i]->get_elements());
        }
    }
}


void ai_model::take_random() {//choose random elements which piece is batch size
    int size = stoi(in->get_shape()[0]);//in matrix 2D matrix
    int row = in->totalsize() / size;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, size - 1);

    vector<vector<int>> indexes;

    int embed_element_size=embed->totalsize()/stoi(embed->get_shape()[0]);//size of an element in embedding matrix

    vector<double> in_v(embed_element_size*mini_batch*row , 0);//token from random elements ordered in same dimension
    vector<double> out_v(embed_element_size*mini_batch, 0);//same thing on out

    for (int i = 0; i < mini_batch; ++i) {//take units as batch size
        int random = dis(gen);//take random row in matrix

        //embed index token from rows value and replace in start and end layers,
        for (int k = 0; k < embed_element_size; ++k) {
            for (int j = 0; j < row; ++j) {//take choosen rows
                int ind=in->_get(random * row + j);
                in_v[embed_element_size*row*i+j*embed_element_size+k]=(embed->_get(embed_element_size*ind+k));
            }
            int el=out->_get(random);
            out_v[embed_element_size*i+k]=(embed->_get(embed_element_size*el+k));
        }
        vector<int> helper_vec;
        for (int j = 0; j < row; ++j) {
            int ind= in->_get(random*row+j);
            helper_vec.push_back(ind);
        }
        indexes.push_back(helper_vec);//indexes hold in a list which provides changed values replace with embedding matrix values
    }
    layers[0]->assign(in_v);
    layers[layers.size()-1]->assign(out_v);//also last layer
}



void ai_model::create_start_end_layers(){    // Preparing layers for SGD and target values

    //Adjust dimensions to starting layer for corresponding values
    vector<string > start_sizes=embed->get_shape(); //dimensions
    start_sizes[0]= to_string(mini_batch);
    int neuron_number=stoi(in->get_shape()[1]);
    start_sizes[1]= to_string(stoi(start_sizes[1]) * neuron_number);

    // Some adjustment for able to various weight values that provide more efficient training ability
    start_sizes[start_sizes.size()-2] = to_string(stoi(start_sizes[start_sizes.size()-1])*stoi(start_sizes[start_sizes.size()-2]));
    start_sizes[start_sizes.size()-1] = to_string(1);

    matrix* start= new matrix("start",start_sizes,-1,1);

    vector<string> end_sizes=start_sizes;
    //dimension normalization

    end_sizes[end_sizes.size()-2]= to_string(stoi(end_sizes[end_sizes.size()-2])/neuron_number);

    matrix* end= new matrix("end",end_sizes,-1,1);

    layers.insert(layers.begin(),start);
    layers.push_back(end);


    for (int i = 1 ; i < layers.size(); ++i) {
        vector<string > sizes = layers[i]->get_shape();
        sizes[sizes.size()-2] = to_string(stoi(sizes[sizes.size()-1])*stoi(sizes[sizes.size()-2]));
        sizes[sizes.size()-1] = to_string(1);

        layers[i]->reshape(sizes);
    }
}


void ai_model::create_weights_and_biases(){
    // Create weight and bias values based on its sizes
    for (int i = 1; i < layers.size(); ++i) {
        vector<string> sizes= layers[i-1]->get_shape();
        sizes[sizes.size()-1]=sizes[sizes.size()-2];
        string last_value=layers[i]->get_shape()[layers[i]->get_shape().size()-2];
        sizes[sizes.size()-2]= last_value;
        weights.push_back(new matrix(to_string(weights.size()),sizes,-1,1));

        bias.push_back(new matrix(to_string(bias.size()),layers[i]->get_shape(),-1,1));
    }
}

void ai_model::save_model(const string & path){
    std::ofstream file(path); // Dosyayı aç

    if (!file.is_open()) {
        throw std::runtime_error("Dosya açılamadı: " + path);
    }
    file<<mini_batch<<"\n";
    for (const string & size : embed->get_shape()) {
        file << size << " ";
    }
    file<<"\n";
    file<<"embed\n";
    for (const double &elem : embed->get_elements()) {
        file << elem << " ";
    }
    file<<"\n";
    for (int i = 0; i < layers.size(); ++i) {
        for (const string & size : layers[i]->get_shape()) {
            file << size << " ";
        }
        file<<"\n";
        file<<"layer"<<i<<"\n";
        for (const double &elem : layers[i]->get_elements()) {
            file << elem << " ";
        }
        file<<"\n";
    }
    for (int i = 0; i < weights.size(); ++i) {
        for (const string & size : weights[i]->get_shape()) {
            file << size << " ";
        }
        file<<"\n";
        file<<"weight"<<i<<"\n";
        for (const double &elem : weights[i]->get_elements()) {
            file << elem << " ";
        }
        file<<"\n";
    }
    for (int i = 0; i < bias.size(); ++i) {
        for (const string & size : bias[i]->get_shape()) {
            file << size << " ";
        }
        file<<"\n";
        file<<"bias"<<i<<"\n";
        for (const double &elem : bias[i]->get_elements()) {
            file << elem << " ";
        }
        file<<"\n";
    }
    file.close();
}
void ai_model::load_model(const std::string &path) {
    std::vector<double> new_matrix;
    std::vector<std::string> string_values;
    std::ifstream file(path);
    std::string line;
    matrix * matrix1;
    int i = 0;

    if (!file.is_open()) throw std::runtime_error("Dosya açılamadı: " + path);
    std::getline(file, line);
    mini_batch= stoi(line);
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        if (i == 1) {
            if (std::equal(line.begin(), line.end(),"embed")) {
                delete embed;
                matrix1 = new matrix("embed",string_values,-1,1);
                embed=matrix1;
            }
            if (std::equal(line.begin(), line.begin()+5,"layer")) {
                matrix1 = new matrix(line,string_values,-1,1);
                layers.push_back(matrix1);
            }
            if (std::equal(line.begin(), line.begin()+6,"weight")) {
                matrix1 = new matrix(line,string_values,-1,1);
                weights.push_back(matrix1);
            }
            if (std::equal(line.begin(), line.begin()+4,"bias")) {
                matrix1 = new matrix(line,string_values,-1,1);
                bias.push_back(matrix1);
            }
            string_values={};
            i=2;
        }
        else if (i == 0) {
            std::string val;
            while (iss >> val) string_values.push_back(val);
            i = 1;
        }
        else if (i == 2) {
            double num;
            while (iss >> num) new_matrix.push_back(num);
            matrix1->assign(new_matrix);
            new_matrix={};
            i = 0;
        }
    }
    file.close();
}

void ai_model::addlayer(vector<string>& sizes) {
    if(layers.size()==0){
        if(embed->dimension()!= sizes.size())throw  std::runtime_error("Boyut değeri geçerli bir tam sayı değil.");
    }else{
        if(layers[layers.size()-1]->dimension()!=sizes.size())throw  std::runtime_error("Boyut değeri geçerli bir tam sayı değil.");
    }

    layers.push_back(new matrix(to_string(layers.size()),sizes,-1,1));
}

void ai_model::eraselayer(const std::string &index) {
    int i = take_index_from_list(index);
    delete layers[i];
    layers.erase(layers.begin()+i);
}

void ai_model::setlayer(const std::string &index,vector<string>& sizes) {
    int i = take_index_from_list(index);

    matrix *matrix1 = new matrix(to_string(layers.size()),sizes,-1,1);
    if(layers[i]->dimension()!=sizes.size())throw  std::runtime_error("Boyut değeri geçerli bir tam sayı değil.");

    layers[i] = matrix1;
}

int ai_model::take_index_from_list(const string &index){
    try {
        int i = std::stoi(index);
        if (i < 0 || i >= layers.size()) {
            throw std::out_of_range("Index out of bounds: " + index);
        }
        return i;

    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid number format: " + index);
    } catch (const std::out_of_range& e) {
        throw std::out_of_range("Index out of bounds: " + index);
    }
}
