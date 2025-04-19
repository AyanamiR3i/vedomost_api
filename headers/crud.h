//dml операции
#ifndef CRUD_H
#define CRUD_H

#include "db.h"
#include <string>
#include <pqxx/pqxx>
#include <map>
#include <vector>

//получить данные из бд
std::string get_data_from_db(std::map<std::string, std::string> env,							
							 PostgresDB& db,
							 std::string filename,
							 std::vector<std::string> vector_params = {});
#endif //CRUD_H
