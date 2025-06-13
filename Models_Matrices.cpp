//
// Created by Lenovo on 5.09.2024.
//

#include "Models_Matrices.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

Model_Matrices::Model_Matrices() {

}
Model_Matrices::~Model_Matrices() {
    for (auto & item : matrix_list) {
        delete item.second;
        matrix_list.erase(item.first);
    }
    for(auto & item: model_list ){
        delete item.second;
        model_list.erase(item.first);
    }
}
string Model_Matrices::predict(string & name , vector<string > inputs){
    return model_list[name]->predict(inputs);
}
matrix* Model_Matrices::get_matrix(string name){
    return matrix_list[name];
}
string Model_Matrices::feed__back(string name){
    int am=model_list[name]->calculate_model_size();
    return to_string(am);
}
void Model_Matrices::create_model(const std::string &name, vector<string> & strings){
    if(matrix_list.find(strings[0])==matrix_list.end()||matrix_list.find(strings[0])==matrix_list.end()){
        //error
    }
    matrix * in = matrix_list[strings[0]];
    matrix * out = matrix_list[strings[1]];
    strings.erase(strings.begin(),strings.begin()+2);
    if(matrix_list.find(name)==matrix_list.end()&&model_list.find(name)==model_list.end()){
        model_list[name]=new ai_model(name, in,out,strings);
    }else{
        //error
    }
}
void Model_Matrices::set_layer(string& object, vector<string > & sizes){
    if(model_list.find(object)!=model_list.end()){
        string in=sizes[0];
        sizes.erase(sizes.begin());
        model_list[object]->setlayer(in , sizes);
    }//error
}
void Model_Matrices::erase_layer(string& object, vector<string > & sizes){
    if(model_list.find(object)!=model_list.end()){
        model_list[object]->eraselayer(sizes[0]);
    }//error
}
void Model_Matrices::add_layer(string& object, vector<string > & sizes){
    if(model_list.find(object)!=model_list.end()){
        model_list[object]->addlayer(sizes);
    }//error
}
string Model_Matrices::_loss(string & object){
        return to_string(model_list[object]->_loss());
}
string Model_Matrices::ai_train(const string& name,const vector<string> &keys){
    if(keys.size()!=2){
        //error
    }
    if(model_list.find(name)!=model_list.end()){
        return to_string(model_list[name]->ai_train(keys[0],keys[1]));
    }else{
        //error
    }
}
void Model_Matrices::reshape_matrix(const std::string &name, const vector<std::string> &sizes) {
    auto it= matrix_list.find(name);
    if(it!= matrix_list.end()){
        it->second->reshape(sizes);
        return;
    }
    throw std::runtime_error("Item can't found. "+ name);
}

string Model_Matrices::_size(const string & name){
    auto  it = matrix_list.find(name);
    if(it!= matrix_list.end()){
        it->second->_size();
    }
}

string Model_Matrices::shape(const string & name) {
    auto  it = matrix_list.find(name);
    if(it!= matrix_list.end()){
        it->second->get_shape();
    }
}

void Model_Matrices::create_matrix(const std::string &name, const vector<std::string> &sizes,int const s1 ,const int s2) {
    if(matrix_list.find(name)==matrix_list.end()&&model_list.find(name)==model_list.end()){
        matrix_list[name]=new matrix(name , sizes , s1,s2);
    }else{
        //error
    }
}

void Model_Matrices::erase(const std::string &name) {
    if( matrix_list.find(name) != matrix_list.end()) {
        delete matrix_list[name];
        matrix_list.erase(name);
        return;
    }
    if (model_list.find(name) != model_list.end()) {
        delete model_list[name];
        model_list.erase(name);
        return;
    }
    throw std::runtime_error("Item can't found. "+ name);
}
void Model_Matrices::read_matrix(const string &name , const string &path){
    if( matrix_list.find(name) != matrix_list.end()) {
        matrix_list[name]->read_matrix(path);
    }
}
void Model_Matrices::write_matrix(const string &name , const string &path){
    if( matrix_list.find(name) != matrix_list.end()) {
        matrix_list[name]->write_matrix(path);
    }
}
void Model_Matrices::save_model(const string &name , const string &path){
    model_list[name]->save_model(path);
}
void Model_Matrices::load_model(const string &name , const string &path){
    model_list[name]->load_model(path);
}