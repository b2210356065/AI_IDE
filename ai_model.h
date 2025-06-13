//
// Created by Lenovo on 4.09.2024.
//

#ifndef AI_COMPIELER_AI_MODEL_H
#define AI_COMPIELER_AI_MODEL_H
#include "string"
#include "vector"
#include "unordered_map"
#include "matrix.h"
#include "math.h"

using namespace std;
class ai_model {
private:

    string name;
    vector<matrix*> layers;
    vector<matrix*> weights;
    vector<matrix*> bias;
    matrix* out;
    matrix* in;
    matrix* embed= nullptr;
    math * mat=nullptr;
    int mini_batch;

    double loss=0;
    int n=0;
public:
    ai_model(const string &name, matrix *&in, matrix *&out,const vector<string> &sizes);

    ~ai_model();
    void addlayer(  vector<string>& sizes);
    void setlayer(const string & index , vector<string>& sizes);
    void eraselayer(const string &index);

    int take_index_from_list(const string &index);

    double ai_train(const string &func_type,const std::string &mini_batch);

    void create_weights_and_biases();


    void deal_with_devil();

    void a_step_ahead();

    void take_random();

    void create_start_end_layers();

    int calculate_model_size();

    double _loss();

    string predict(vector<string> &ins);

    void save_model(const string &path);

    void load_model(const string &path);
};


#endif //AI_COMPIELER_AI_MODEL_H
