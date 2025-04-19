#ifndef DB_H
#define DB_H

#include <string>
#include <pqxx/pqxx>
#include <map>

class PostgresDB {
private:
    std::string* conn_str;
    pqxx::connection* connection;
    pqxx::work* work_obj;

    // запрещаем копирование
    PostgresDB(const PostgresDB&) = delete;
    PostgresDB& operator=(const PostgresDB&) = delete;

public:
    explicit PostgresDB(const std::map<std::string, std::string>& env);
    ~PostgresDB();

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
