//
// Created by Lenovo on 3.09.2024.
//
#include <stdexcept>
#include <iostream>
#include "methods.h"
#include "vector"
using namespace std;



methods::methods():models_matrices(new Model_Matrices()) {
    funcMap = {
            {"new_model", std::bind(&methods::new_model, this, std::placeholders::_1, std::placeholders::_2)},
            {"add_layer", std::bind(&methods::add_layer, this, std::placeholders::_1, std::placeholders::_2)},
            {"ai_train", std::bind(&methods::ai_train, this, std::placeholders::_1, std::placeholders::_2)},
            {"erase", std::bind(&methods::erase, this, std::placeholders::_1, std::placeholders::_2)},
            {"load_model", std::bind(&methods::load_model, this, std::placeholders::_1, std::placeholders::_2)},
            {"loss", std::bind(&methods::loss, this, std::placeholders::_1, std::placeholders::_2)},
            {"matrix_reshape", std::bind(&methods::matrix_reshape, this, std::placeholders::_1, std::placeholders::_2)},
            {"predict", std::bind(&methods::predict, this, std::placeholders::_1, std::placeholders::_2)},
            {"save_model", std::bind(&methods::save_model, this, std::placeholders::_1, std::placeholders::_2)},
            {"set_layer", std::bind(&methods::set_layer, this, std::placeholders::_1, std::placeholders::_2)},
            {"shape", std::bind(&methods::shape, this, std::placeholders::_1, std::placeholders::_2)},
            {"_size", std::bind(&methods::_size, this, std::placeholders::_1, std::placeholders::_2)},
            {"create_matrix", std::bind(&methods::create_matrix, this, std::placeholders::_1, std::placeholders::_2)},
            {"erase_layer", std::bind(&methods::erase_layer, this, std::placeholders::_1, std::placeholders::_2)},
            {"read_matrix", std::bind(&methods::read_matrix, this, std::placeholders::_1, std::placeholders::_2)},
            {"write_matrix", std::bind(&methods::write_matrix, this, std::placeholders::_1, std::placeholders::_2)}


    };
}
methods::~methods() {
    delete models_matrices;
}

string methods::choose_method(vector<string> &strings) {
    if (strings.size() < 2) {
        throw std::invalid_argument("There is a wrong command in your code :"+strings[0]);
    }

    string func_name = strings[0];
    string object_name = strings[1];

    strings.erase(strings.begin(), strings.begin() + 2);

    auto it = funcMap.find(func_name);
    if (it == funcMap.end()) {
        throw std::invalid_argument("There is a wrong command in your code :"+func_name);
    }

    auto func = it->second;
    return func(object_name, strings);
}



string methods::ai_train(string  & object , vector<string> & strings){
    return "Loss changed from "+models_matrices->_loss(object)+" to "+ models_matrices->ai_train(object,strings);
}

string methods::new_model(string &object, vector<string> &strings) {
    models_matrices->create_model(object , strings);
    return models_matrices->feed__back(object);
}

string methods::add_layer(string &object, vector<string> &strings) {
    models_matrices->add_layer(object , strings);
    return "Layer added.";
}

string methods::load_model(string &object, vector<string> &strings) {
    models_matrices->load_model(object,strings[0]);
    return "Model loaded.";
}

string methods::loss(string &object, vector<string> &strings) {
    if(strings.size()!=0);//error;
    string out =models_matrices->_loss(object);
    return out;
}
string methods::save_model(string &object, vector<string> &strings) {
    models_matrices->save_model(object,strings[0]);
    return "Model saved.";
}

string methods::set_layer(string &object, vector<string> &strings) {
    models_matrices->set_layer(object, strings);
    return "Layer set.";
}

string methods::shape(string &object, vector<string> &strings) {
    if(strings.size()!=0)//erorr;
    return models_matrices->shape(object);
}

string methods::erase(string &object, vector<string> &strings) {
    if(strings.size()!=0){
        //error
    }
    models_matrices->erase(object);
    return "Data erased.";
}

string methods::_size(string &object, vector<string> &strings) {
    if(strings.size()!=0)//error;
    return   models_matrices->_size(object);

}
string methods::create_matrix(string &object, vector<string> &strings){
    if(strings.size()!=4){
        //error
    }
    int s1= stoi(strings[strings.size()-2]);
    int s2= stoi(strings[strings.size()-1]);
    strings.erase(strings.end()-2,strings.end());
    models_matrices->create_matrix(object, strings,s1,s2);
    return models_matrices->get_matrix(object)->_size();
}
string methods::erase_layer(string&object ,vector<string> & strings){
    if(strings.size()!=1)//error;
    models_matrices->erase_layer(object, strings);
    return "Layer erased";
}
string methods::matrix_reshape(string &object, vector<string> &strings) {
    models_matrices->reshape_matrix(object, strings);
    return "Matrix reshaped.";
}
string methods::predict(string &object, vector<string> &strings) {
    models_matrices->predict(object,strings);
    return "Image processed.";
}
string methods::write_matrix(std::string &object, vector<std::string> &strings) {
    models_matrices->write_matrix(object, strings[0]);
    return "Wrote in txt";
}
string methods::read_matrix(std::string &object, vector<std::string> &strings) {
    models_matrices->read_matrix(object, strings[0]);
    return "Read in txt";
}



