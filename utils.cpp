#include "headers/utils.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

std::vector<std::string> split(const std::string& str, char delimiter)
{
        //разбиение строки по разделителю
        std::vector<std::string> tokens;
        std::string token;
        std::stringstream ss(str);

        while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
        }

        return tokens;
}

std::string read_sql_file(std::map<std::string, std::string> env, std::string filename){
        std::string path = env["SQL_PATH"] + filename;
        std::ifstream sql(path);
        std::string result = "";
        if(!sql.is_open()){
                std::cerr<<"Не удалось открыть файл!"<<std::endl;
        } else{
                std::string line;
                
                while(std::getline(sql, line)){
                        result += line;
                }
        }
        sql.close();
        return result;
}
