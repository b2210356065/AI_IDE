//
// Created by Lenovo on 5.09.2024.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include "matrix.h"
matrix::matrix(const std::string &name, const std::vector<std::string> &sizes, const double s1,const double s2) : name(name) {
    for (const std::string &size : sizes) {
        size_t pos;
        int sz = std::stoi(size, &pos);

        if (pos != size.size()) {
            throw std::runtime_error("Boyut değeri geçerli bir tam sayı değil.");
        }
        if (sz <= 0) {
            throw std::runtime_error("Boyut değeri pozitif olmalıdır.");
        }
        this->sizes.push_back(sz);
        total_size *= sz;
    }

    int sum = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(s1, s2);

    for (int i = 0; i < total_size; ++i) {
        double random_value = dis(gen);
        elements.push_back(random_value);
        sum += random_value;
    }
}


void matrix::reshape(const std::vector<std::string> &sizes) {
    int length = this->sizes.size();
    for (const std::string &size : sizes) {
        size_t pos;
        int sz = std::stoi(size, &pos);

        if (pos != size.size()) {
            throw std::runtime_error("Boyut değeri geçerli bir tam sayı değil.");
        }
        if (sz <= 0) {
            throw std::runtime_error("Boyut değeri pozitif olmalıdır.");
        }
        this->sizes.push_back(sz);
    }
    this->sizes.erase(this->sizes.begin(), this->sizes.begin() + length);
    rearrange_totalsize();
}
void matrix::assign(const vector<double > & list){
    int size = list.size();
    if(list.size()!=total_size){throw std::runtime_error("Boyut değeri pozitif olmalıdır.");}
    for (int i = 0; i < list.size(); ++i) {
        elements[i]=list[i];
    }
}

void matrix::read_matrix(const std::string &path) {
    std::vector<double> new_matrix;
    std::ifstream file(path); // Dosyayı aç

    if (!file.is_open()) {
        throw std::runtime_error("Dosya açılamadı: " + path);
    }

    double value;
    while (file >> value) {
        new_matrix.push_back(value);
    }
    this->elements = new_matrix;

    file.close();
}

void matrix::write_matrix(const std::string &path) const {
    std::ofstream file(path); // Dosyayı aç

    if (!file.is_open()) {
        throw std::runtime_error("Dosya açılamadı: " + path);
    }

    for (const double &elem : elements) {
        file << elem << " ";
    }
    file << std::endl;

    file.close();
}
string matrix::_shape(){
    string shape= to_string(sizes[0]);

    for (int i = 1; i < sizes.size(); ++i) {
        shape+=","+ to_string(sizes[i]);
    }
    return shape;
}
string matrix::_size(){
    return to_string(total_size);
}
vector<string > matrix::get_shape() {
    vector<string > vec;
    for (int i = 0; i < sizes.size(); ++i) {
        vec.push_back(to_string(sizes[i]));
    }
    return vec;
}

int matrix::dimension(){
    return sizes.size();
}
int matrix::totalsize(){
    return total_size;
}
vector<double>matrix::get_elements(){
    return elements;
}

void matrix::put_value(const int index, const double value) {
    elements[index]=value;
}
double matrix::_get(const int i){
    return elements[i];
}
void matrix::rearrange_totalsize(){
    total_size=1;
    for (int i = 0; i < sizes.size(); ++i) {
        total_size*= sizes[i];
    }
}
void matrix::put_interval(const vector<double>  & replace, int i){
    copy(replace.begin(),replace.end(), elements.begin()+i);
}