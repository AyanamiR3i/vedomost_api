//работа с сервером, эндпоинты
#ifndef ROUTING_H
#define ROUTING_H

#include "httplib.h"
#include "db.h"
#include <map>
#include <string>

//базовый эндопоинт
void base(httplib::Server& server);

//получить все учебные группы
void get_groups(httplib::Server& server, std::map<std::string, std::string>& env, PostgresDB& db);
				

//инициализация сервера, регистрация эндпоинтов, запуск
void create_server(std::map<std::string, std::string>& env, PostgresDB& db);



#endif 