//инстанс приложения
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <pqxx/pqxx>
#include "headers/db.h"
#include "headers/crud.h"
#include "headers/routing.h"
#include "headers/utils.h"


int main() {
    #ifdef CPPHTTPLIB_THREAD_POOL_COUNT
    std::cout << "Thread pool support enabled\n";
    #else
    std::cout << "Thread pool DISABLED\n";
    #endif
    std::map<std::string, std::string> env = get_env(".env");
    PostgresDB db = PostgresDB(env);
    if (db.is_connected()) {
        std::cout << "Все гуд" << std::endl;
        //std::string groups = get_data_from_db(env, db, "get_study_groups.sql");
        //std::cout <<groups<< std::endl;
        create_server(env, db);
    } else {
        std::cout << "Подключение умерло" << std::endl;
    }
    return 0;
}
