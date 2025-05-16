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
#include <thread>


int main() {
    #ifdef CPPHTTPLIB_THREAD_POOL_COUNT
    std::cout << "Thread pool support enabled\n";
    #else
    std::cout << "Thread pool DISABLED\n";
    #endif
    std::map<std::string, std::string> env = get_env(".env");
    PostgresDB db = PostgresDB(env);
    if (db.is_connected()) {
        std::cout << "Подключаемся к базе данных..." << std::endl;
        std::thread server_thread(create_server, std::ref(env), std::ref(db));
        std::cout << "Сервер запущен на http://" << env["API_HOST"] << ":" << env["API_PORT"] << "\n";
        server_thread.join();
    } else {
        std::cout << "Подключение умерло" << std::endl;
    }
    return 0;
}