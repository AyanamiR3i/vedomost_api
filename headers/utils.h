//utils.h
#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <string>
#include <fstream>
#include <map>

//разбиение строки по разделителю
std::vector<std::string> split(const std::string& str, char delimiter);

//прочитать sql файл и вернуть в виде строки
std::string read_sql_file(std::map<std::string, std::string> env, std::string filename);

#endif //UTILS_H
