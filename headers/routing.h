//работа с сервером, эндпоинты
#ifndef ROUTING_H
#define ROUTING_H

#include "httplib.h"
#include "db.h"
#include <map>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//установка заголовков запроса (параметры: ссылка на объект запроса, имя http-метода)
void set_headers(httplib::Response& res, std::string method);

//страница для групп (параметры: ссылка на объект сервера)
void base_groups(httplib::Server& server);

//получить все учебные группы (параметры: ссылка на объект сервера, ссылка на окружение, ссылка на объект бд)
void get_groups(httplib::Server& server, std::map<std::string, std::string>& env, PostgresDB& db);

//добавить учебную группу (параметры: ссылка на объект сервера, ссылка на окружение, ссылка на объект бд)
void add_group(httplib::Server& server, std::map<std::string, std::string>& env, PostgresDB& db);

//удалить учебную группу (параметры: ссылка на объект сервера, ссылка на окружение, ссылка на объект бд)
void delete_group(httplib::Server& server, std::map<std::string, std::string>& env, PostgresDB& db);

//инициализация сервера, регистрация эндпоинтов, запуск (параметры: ссылка на окружение, ссылка на объект бд)
void create_server(std::map<std::string, std::string>& env, PostgresDB& db);

#endif 