//dml операции
#ifndef CRUD_H
#define CRUD_H

#include "db.h"
#include <string>
#include <pqxx/pqxx>
#include <map>

//получить список учебных групп из бд
std::string get_groups(std::map<std::string, std::string> env, PostgresDB& db);

#endif //CRUD_H
