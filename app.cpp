//инстанс приложения
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <pqxx/pqxx>
#include "headers/init.h"
#include "headers/db.h"
#include "headers/crud.h"

int main() {
    InitApp app = InitApp();
    std::map<std::string, std::string> env = app.get_app_env(app.get_env_value());
    PostgresDB db = PostgresDB(env);
    if (db.is_connected()) {
        std::cout << "Все гуд" << std::endl;
    } else {
        std::cout << "Подключение умерло" << std::endl;
    }

    //pqxx::work work_obj = db.get_database_obj(session);
    //pqxx::result groups = get_groups(env, work_obj);

    return 0;
}
