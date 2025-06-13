//
// Created by Lenovo on 5.09.2024.
//

#ifndef AI_COMPIELER_MATRICES_H
#define AI_COMPIELER_MATRICES_H
#include "matrix.h"
#include "unordered_map"
#include "ai_model.h"
using namespace std;
class Model_Matrices {

private:
    unordered_map<string , matrix* > matrix_list;
    unordered_map<string , ai_model*> model_list;
public:
    Model_Matrices();
    ~Model_Matrices();
    void create_matrix(const string &name, const vector<string>&sizes,int const s1 ,const int s2);
    void erase(const string &name);
    void reshape_matrix(const string & name ,const vector<string>&sizes );

    string shape(const string &name);

    string _size(const string &name);

    void create_model(const string &name, vector<string> & strings);

    string ai_train(const string &name , const vector<string> &keys);

    void set_layer(string &object, vector<string> &sizes);

    string _loss(string &object);

    void add_layer(string &object, vector<string> &sizes);

    void erase_layer(string &object, vector<string> &sizes);

    matrix *get_matrix(string name);

    string feed__back(string name);

    void read_matrix(const string &name, const string &path);

    void write_matrix(const string &name, const string &path);

    string predict(string &name, vector<string> inputs);

    void save_model(const string &name, const string &path);

    void load_model(const string &name, const string &path);
};


#endif //AI_COMPIELER_MATRICES_H
