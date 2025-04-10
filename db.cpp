#include "headers/db.h"
#include <pqxx/pqxx>
#include <sstream>
#include <stdexcept>
#include <iostream>

PostgresDB::PostgresDB(const std::map<std::string, std::string>& env) 
    : conn_str(nullptr), connection(nullptr), work_obj(nullptr) {
    try {
        // Формируем строку подключения
        std::stringstream stream_conn;
        stream_conn << "dbname=" << env.at("DB_NAME")
                   << " user=" << env.at("DB_USER")
                   << " password=" << env.at("DB_PASSWORD")
                   << " hostaddr=" << env.at("DB_HOST")
                   << " port=" << env.at("DB_PORT");
        
        conn_str = new std::string(stream_conn.str());
        
        // Создаём соединение
        connection = new pqxx::connection(*conn_str);
        
        // Создаём транзакцию
        work_obj = new pqxx::work(*connection);
        
    } catch (...) {
        // При ошибке освобождаем уже выделенные ресурсы
        delete work_obj;
        delete connection;
        delete conn_str;
        throw;
    }
}

PostgresDB::~PostgresDB() {
    delete work_obj;     // Удаляем в обратном порядке создания
    delete connection;
    delete conn_str;
}

 bool PostgresDB::is_connected(){
        return connection && connection->is_open();
 }

void PostgresDB::commit() {
    if (work_obj) {
        try {
            work_obj->commit();
        } catch (...) {
            // При ошибке коммита делаем rollback
            rollback();
            throw;
        }
    }
}

void PostgresDB::rollback() {
    if (work_obj) {
        try {
            work_obj->abort();
        } catch (...) {
            // Игнорируем ошибки при откате
        }
    }
}

pqxx::result PostgresDB::execute(const std::string& sql) {
    if (!work_obj) {
        throw std::runtime_error("No active transaction");
    }
    return work_obj->exec(sql);
}