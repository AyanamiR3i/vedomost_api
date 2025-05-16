#include "headers/utils.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, std::string> get_env(std::string path){
        std::map<std::string, std::string> env;
        std::ifstream file(path);
        std::string line;
    
        while (std::getline(file, line)) {
                // Ищем позицию знака '='
                size_t pos = line.find('=');
                if (pos != std::string::npos) {
                    std::string key = line.substr(0, pos);
                    std::string value = line.substr(pos + 1);
                    env[key] = value;
                }
        }
    
        return env;
}


std::string read_file(std::string filepath){
        std::ifstream file(filepath);
        std::string result = "";
        if(!file.is_open()){
                std::cerr<<"Не удалось открыть файл!"<<std::endl;
        } else{
                std::string line;
                
                while(std::getline(file, line)){
                        result += line;
                }
        }
        file.close();
        return result;
}

json result_to_json(const pqxx::result& res){
        json j = json::array();
    
        for (const auto& row : res) {
        json j_row;
        for (const auto& field : row) {
            j_row[field.name()] = field.is_null() ? nullptr : field.c_str();
        }
        j.push_back(j_row);
    }
    
    return j;
}
