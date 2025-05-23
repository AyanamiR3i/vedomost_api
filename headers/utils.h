//utils.h
#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <pqxx/pqxx>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//прочитать файл окружения
std::map<std::string, std::string> get_env(std::string path);

//прочитать sql файл и вернуть в виде строки
std::string read_file(std::string filepath);

//преобразовать pqxx::result в json
json result_to_json(const pqxx::result& res);

//очистить строку от кавычек
std::string clear_string(std::string old_string);
#endif //UTILS_H
