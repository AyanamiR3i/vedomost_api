//инстанс приложения
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <pqxx/pqxx>
#include "headers/init.h"
#include "headers/db.h"

int main() {
    InitApp app = InitApp();
    std::map<std::string, std::string> env = app.get_app_env(app.get_env_value());
    PostgresDB db = PostgresDB();

    std::string conn_str = *db.get_connection_str(env);
    pqxx::connection& session = db.get_session(conn_str);
    if (session.is_open()) {
        std::cout << "Все гуд" << std::endl;
    } else {
        std::cout << "Подключение умерло" << std::endl;
    }

    pqxx::work obj = db.get_database_obj(session);

    return 0;
}
