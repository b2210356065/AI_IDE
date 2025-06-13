//
// Created by Lenovo on 3.09.2024.
//

#ifndef AI_COMPIELER_METHODS_H
#define AI_COMPIELER_METHODS_H

#include <vector>
#include <unordered_map>
#include <functional>
#include "string"
#include "Models_Matrices.h"

using namespace std;

class methods {


private:
    string new_model(string &object,vector<string > &strings);
    string add_layer(string &object,vector<string > &strings);
    string erase(string &object,vector<string > &strings);
    string load_model(string &object,vector<string > &strings);
    string loss(string &object,vector<string > &strings);
    string matrix_reshape(string &object,vector<string > &strings);
    string predict(string &object, vector<string > &strings);
    string save_model(string &object,vector<string > &strings);
    string set_layer(string &object,vector<string > &strings);
    string shape(string &object,vector<string > &strings);
    string _size(string &object,vector<string > &strings);
    string ai_train(string &object, vector<string> &strings);
    string create_matrix(string &object, vector<string> &strings);
    string erase_layer(string &object, vector<string> &strings);
    string read_matrix(string &object, vector<std::string> &strings);
    string write_matrix(string &object, vector<string> &strings);



public:
    methods();
    ~methods();

    std::unordered_map<std::string, std::function<string(string&, vector<string>&)>> funcMap;
    Model_Matrices *models_matrices= nullptr;
    std::string choose_method(vector<string>&strings);

};


#endif //AI_COMPIELER_METHODS_H
