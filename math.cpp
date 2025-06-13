//
// Created by Lenovo on 11.09.2024.
//

#include <string>
#include <cmath>
#include <iostream>
#include "math.h"
#include "matrix.h"

using namespace std;
math::math(const string& func_name) {
    name= "tanh";
}
double math::take_derivative(double value) {
    double tanh_value = std::tanh(value);
    return 1 - tanh_value * tanh_value;
}

double math::loss(const vector<double> &ele1,const vector<double> &ele2){//mean square loss function
    double loss=0;
    int size = ele1.size();
    for (int i = 0; i < ele1.size(); ++i) {
        loss+=(ele1[i]-ele2[i])*(ele1[i]-ele2[i]);
    }
    return loss/size;
}
vector<double> math::out(matrix* matrix1, matrix * matrix2, matrix* matrix3, matrix *matrix4){
    vector<double> new_matrix;

    vector<string> sizes= matrix1->get_shape();
    int h=stoi(sizes[sizes.size()-2]);
    int w= stoi(sizes[sizes.size()-1]);
    int h2= stoi(matrix2->get_shape()[matrix2->get_shape().size()-1]);

    sizes.erase(sizes.end());
    sizes.push_back(to_string(h2));
    int upper_dimensions_size= matrix1->totalsize()/(w*h);


    for (int r = 0; r < upper_dimensions_size; ++r) {//upper dimensions act like parallel ordinal so all segment of 2-D Model_Matrices&Matrices can examine iterative at upper dimensions
        for (int i = 0; i < h; ++i) {//first Model_Matrices&Matrices height
            for (int j = 0; j < h2; ++j) {//second Model_Matrices&Matrices width//
                double sum = 0;
                double v3 = matrix3->_get(r*h*h2+i*h2+j);
                for (int k = 0; k < w; ++k) {
                    double v1=matrix1->_get(i*w+k+w*h*r);
                    double v2=matrix2->_get(j+k*h2+h2*w*r);
                    sum+=v1*v2;//primitive stage of matrix multiplication
                }
                sum+=v3;
                sum= approve_function(sum);
                new_matrix.push_back(sum);
            }
        }
    }
    return new_matrix;
}

vector<double> math::gradient_calculation(matrix* matrix1, matrix * matrix2, matrix* matrix3, matrix *matrix4,double c){
    vector<double> new_matrix;

    vector<string> sizes= matrix1->get_shape();
    int h=stoi(sizes[sizes.size()-2]);
    int w= stoi(sizes[sizes.size()-1]);
    int h2= stoi(matrix2->get_shape()[matrix2->get_shape().size()-1]);

    sizes.erase(sizes.end());
    sizes.push_back(to_string(h2));
    int upper_dimensions_size= matrix1->totalsize()/(w*h);

    for (int r = 0; r < upper_dimensions_size; ++r) {//upper dimensions act like parallel ordinal so all segment of 2-D Model_Matrices&Matrices can examine iterative at upper dimensions
        for (int i = 0; i < h; ++i) {//first Model_Matrices&Matrices height
            for (int j = 0; j < h2; ++j) {//second Model_Matrices&Matrices width
                double sum=0;
                for (int k = 0; k < w; ++k) {//first Model_Matrices&Matrices width also second Model_Matrices&Matrices height
                    int index1 = i*w+k+w*h*r; // Value from weight
                    int index2 = j+k*h2+h2*w*r; // Value from input

                    double v1=matrix1->_get(index1);
                    double v2=matrix2->_get(index2);
                    sum+=v1*v2; //sum of multiplication of input and weight values
                }
                sum+=matrix3->_get(r*h*h2+i*h2+j); //add bias

                double v4=matrix4->_get(r*h*h2+i*h2+j); // Compare sum value with corresponding output value
                double s = approve_function(sum); //tanh
                double t =take_derivative(sum); // dTanhx/dX
                double coef=(s-v4)* t *c; // Derivative of Loss for single value


                for (int k = 0; k < w; ++k) {
                    int index1 = i*w+k+w*h*r;// Value from weight
                    int index2 = j+k*h2+h2*w*r;// Value from input


                    double gr_des1=coef*matrix2->_get(index2); // Calculate gradient vectors
                    double gr_des2=coef*matrix1->_get(index1);


                    double v1=matrix1->_get(index1); // Get initial value that it will change
                    double v2=matrix2->_get(index2);


                    double new_value1=v1-gr_des1;//change initial values with through gradient vectors
                    double new_value2=v2-gr_des2;//change initial values with through gradient vectors


                    matrix1->put_value(index1,new_value1);// Replace changed value with initial value
                    matrix2->put_value(index2,new_value2);
                }

                double new_value3=matrix3->_get(r*h*h2+i*h2+j)-(coef); //change initial values with through gradient vectors

                matrix3->put_value(r*h*h2+i*h2+j,new_value3); //Replace changed value with initial value

                sum = 0; // calculate output
                for (int k = 0; k < w; ++k) {
                    int index1 = i*w+k+w*h*r;
                    int index2 = j+k*h2+h2*w*r;

                    double v1=matrix1->_get(index1); // new values
                    double v2=matrix2->_get(index2);
                    sum+=v1*v2;//primitive stage of matrix multiplication
                }
                sum+=new_value3; //add bias

                sum= approve_function(sum); //tanh
                new_matrix.push_back(sum); //output
            }
        }
    }
    return new_matrix;
}


double math::approve_function(double x){
    return std::tanh(x);
}
