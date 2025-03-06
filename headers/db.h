//низкоуровневая работа с бд
#ifndef DB_H
#define DB_H

#include <string>
#include <pqxx/pqxx>
#include <string>

class PostgresDB{
public:
	//формирование строки подключения к бд
	std::unique_ptr<std::string> get_connection_str(std::map<std::string, std::string> env);

	//получение объекта соединения с бд
    pqxx::connection& get_session(const std::string& conn_str);

    //получить транзакционный объект
    pqxx::work get_database_obj(pqxx::connection& connection);

    // сделать коммит
    void commit(pqxx::work& work);

private:
    std::unique_ptr<pqxx::connection> connection;
};

#endif //DB_H
