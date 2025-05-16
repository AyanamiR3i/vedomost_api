#ifndef DB_H
#define DB_H

#include <string>
#include <pqxx/pqxx>
#include <map>

class PostgresDB {
private:
    //строка подключения
    std::string* conn_str; 

    //указатель на объект подключения
    pqxx::connection* connection;

    //указатель на объект транзакции для работы с бд 
    pqxx::work* work_obj;

    // запрещаем копирование
    PostgresDB(const PostgresDB&) = delete;
    PostgresDB& operator=(const PostgresDB&) = delete;

public:
    explicit PostgresDB(const std::map<std::string, std::string>& env);
    ~PostgresDB();

    //структура для хранения параметров запросов
    struct params{ 
        int int_param = -1;
        double double_param = -1.0;
        std::string string_param = "";
    };

    //проверка соединения
    bool is_connected();

    //сделать коммит
    void commit();

    //откатить транзакцию
    void rollback();

    //выполнить sql-запрос
    pqxx::result execute(const std::string& sql, pqxx::params params);
};

#endif //DB_H
