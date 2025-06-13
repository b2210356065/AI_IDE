//
// Created by Lenovo on 31.08.2024.
//

#include "arrange_strings.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include "string"
using namespace std;
arrange_strings::arrange_strings():Methods(new methods()) {

}
arrange_strings::~arrange_strings() {
    delete Methods;
}

std::vector<std::string> arrange_strings::split_line(const std::string& input) {
    // 5 elemanlı sonuç vektörü
    std::vector<std::string> result(5, "");
    int condition = 0;
    for (char c : input) {
        if (c == '(') {
            condition = 1;
        } else if (c == ')' && condition == 1) {
            result[condition] += c;
            condition = 2;
            continue;
        } else if (c == '#') {
            condition = 3;
        }
        result[condition] += c;
    }

    result[4] = _tab(input, '\t');

    return result;
}

void arrange_strings::arrange_split_line(vector<string> & result){
    if(result[0]=="o"&&result[2].length()==0){
        if(result[1].length()==0){
            result[0]="o()";
        }
        return;
    }
    for (const auto& pair : prefix_map) {
        if (result[0].size() >= pair.first.length() &&
            result[0].substr(0, pair.first.length()) == pair.first) {
            if(result[4]=="1"){
                result[0] = pair.second;
                if(result[1].length()==0)result[1]="()";
            }
            if(result[0]==pair.second)return;
        }
    }
    result[2]=result[0]+result[1]+result[2];
    result[0]="";
    result[1]="";
}

void arrange_strings::run(vector<string> &lines){
    for (string &line: lines) {
        compile_line(line);
    }
}

string arrange_strings::compile_line(string &line){
    vector<string > parts= split_line(line);
    arrange_split_line(parts);

    parts[2].erase(std::remove(parts[2].begin(),parts[2].end(), ' '), parts[2].end());

    if(parts[2].length()!=0)        throw std::invalid_argument("There is a wrong command in your code :"+line);

    string in_brackets=parts[1];

    parts.erase(parts.end()-4,parts.end());

    regex re("[(),\\s]+");
    sregex_token_iterator iter(in_brackets.begin(), in_brackets.end(), re, -1);
    sregex_token_iterator end;

    for (; iter != end; ++iter) {
        string part = *iter;
        if (!part.empty()) {
            parts.push_back(part);
        }
    }
    return Methods->choose_method(parts);
}

string arrange_strings::play_lines(string& input){
    try {
        if(_tab(input,'\\')=="1"){
            return compile_line(input);
        }
        return "";
    }catch (...){
        return "An error occured";
    }

}


string arrange_strings::_tab(const string  & input, const char c){
    if (!input.empty() && input.back() == c) {
        return "1";
    } else {
        return "0";
    }
}


vector<string> arrange_strings::split_string(const std::string &input, const char c) {
    vector<std::string> result;
    string token;
    istringstream tokenStream(input);

    while (std::getline(tokenStream, token, c)) {
        result.push_back(token);
    }
    for (int i = 1; i < result.size(); ++i) {
        result[i]='\\'+result[i];
    }
    while (result.size()<2)result.push_back("");

    return result;
}

