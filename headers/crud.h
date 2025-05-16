//dml операции
#ifndef CRUD_H
#define CRUD_H

#include "db.h"
#include <string>
#include <pqxx/pqxx>
#include <map>
#include <vector>

//получение и отправка данных в бд (параметры: ссылка на окружение, ссылка на объект бд, имя sql-файла, параметры запроса)
std::string exec_sql(std::map<std::string, std::string> env,							
							 PostgresDB& db,
							 std::string filename,
							 std::vector<PostgresDB::params> vector_params = {});
#endif //CRUD_H
