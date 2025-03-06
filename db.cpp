// работа с бд
#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include "headers/db.h"
#include <pqxx/pqxx>

std::unique_ptr<std::string> PostgresDB::get_connection_str(std::map<std::string, std::string> env){
	std::stringstream stream_conn;
	try {
	stream_conn << "dbname="<<env.at("DB_NAME")<<" user="<<env.at("DB_USER")
	<<" password="<<env.at("DB_PASSWORD")<<" hostaddr="<<env.at("DB_HOST")
	<<" port="<<env.at("DB_PORT");
	std::unique_ptr<std::string> string_stream = std::make_unique<std::string>(stream_conn.str());
	return string_stream;
	} catch (const std::out_of_range& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return nullptr;
	}
}

pqxx::connection& PostgresDB::get_session(const std::string& conn_str) {
    try {
        connection = std::make_unique<pqxx::connection>(conn_str);
        return *connection;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        throw;
    }
}

pqxx::work PostgresDB::get_database_obj(pqxx::connection& connection) {
    try {
        return pqxx::work(connection);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        throw;
    }
}

void PostgresDB::commit(pqxx::work& work){
    try {
        work.commit();
    } catch (const std::exception& e){
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}
