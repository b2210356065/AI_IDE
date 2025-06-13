//
// Created by Lenovo on 11.09.2024.
//

#ifndef AI_COMPIELER_MATH_H
#define AI_COMPIELER_MATH_H
#include "string"
#include "matrix.h"

using namespace std;
class math {
private:
    string name;
    double slope=1;
    double prev_loss=300;
public:
    math(const string &name);

    double take_derivative(double value);

    double approve_function(double value);

    static double loss(const vector<double> &ele1,const vector<double> &ele2);

    vector<double> gradient_calculation(matrix *matrix1, matrix *matrix2, matrix* matrix3, matrix *matrix4, double coef);

    vector<double> out(matrix *matrix1, matrix *matrix2, matrix *matrix3, matrix *matrix4);
};


#endif //AI_COMPIELER_MATH_H
