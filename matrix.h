//
// Created by Lenovo on 5.09.2024.
//

#ifndef AI_COMPIELER_MATRIX_H
#define AI_COMPIELER_MATRIX_H
#include "vector"
#include "string"

using namespace std;
class matrix {
private:
    int total_size=1;
    vector<int> sizes;
    vector<double> elements;
public:
    string name;
    matrix(const string &name, const vector<string>&sizes, const double s1,const double s2);
    void reshape(const vector<string> &sizes);
    void read_matrix(const string &path);
    void write_matrix(const string &path) const;

    void assign(const vector<double> &list);
    void put_value(const int index , const double value);

    string _shape();

    string _size();

    vector<string> get_shape();

    int dimension();

    int totalsize();

    double _get(const int i);

    vector<double> get_elements();

    void rearrange_totalsize();

    void put_interval(const vector<double> &replace, int i);
};


#endif //AI_COMPIELER_MATRIX_H
