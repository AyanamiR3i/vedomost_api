//низкоуровневая работа с бд
#ifndef DB_H
#define DB_H

#include <string>
#include <pqxx/pqxx>
#include <string>


std::string* get_connection_str(std::map<std::string, std::string> env);
//формирование строки подключения к бд

//получение объекта соединения с бд
pqxx::connection get_session(std::map<std::string, std::string> env);

#endif //DB_H
