//низкоуровневая работа с бд
#include <map>
#include <sstream>
#include <string>
#include "headers/db.h"
#include <pqxx/pqxx>

std::string* get_connection_str(std::map<std::string, std::string> env){
	std::stringstream stream_conn;
	try {
	stream_conn << "dbname="<<env.at("DB_NAME")<<" user="<<env.at("DB_USER")
	<<" password="<<env.at("DB_PASSWORD")<<" hostaddr="<<env.at("DB_HOST")
	<<" port="<<env.at("DB_PORT");
	std::string string_stream = new std::string(stream_conn.str());
	return string_stream;
	} catch (const std::out_of_range& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return nullptr;

}

pqxx::connection get_session(std::map<std::string, std::string> env){
	return pqxx::connection(get_connection_str(env));
}
