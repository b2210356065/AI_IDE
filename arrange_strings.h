//
// Created by Lenovo on 31.08.2024.
//

#ifndef AI_COMPIELER_ARRANGE_STRINGS_H
#define AI_COMPIELER_ARRANGE_STRINGS_H

#include <functional>
#include <variant>
#include "string"
#include "vector"
#include "unordered_map"
#include "methods.h"

class arrange_strings {
private:
    methods *Methods;
    const std::unordered_map<std::string, std::string> prefix_map{
            {"ad", "add_layer"},
            {"ai", "ai_train"},
            {"cr", "create_matrix"},
            {"er", "erase"},
            {"el", "erase_layer"},
            {"loa","load_model"},
            {"los","loss"},
            {"re", "read_matrix"},
            {"ne", "new_model"},
            {"ma", "matrix_reshape"},
            {"mo", "models_function"},
            {"pr", "predict"},
            {"sa", "save_model"},
            {"se", "set_layer"},
            {"sh", "shape"},
            {"si", "_size"},
            {"wr", "write_matrix"},
            {"tr", "transform_layer"},
    };
public:
    arrange_strings();
    ~arrange_strings();
    vector<std::string> split_line(const std::string &input);


    void arrange_split_line(std::vector<std::string> &result);

    string play_lines(std::string &input);

    void run(std::vector<std::string> &lines);

    string compile_line(std::string &line);

    string _tab(const string &input, const char c);

    vector<string> split_string(const string &input,const char c);
};


#endif //AI_COMPIELER_ARRANGE_STRINGS_H
