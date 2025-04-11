//dml операции

#include "headers/crud.h"
#include <pqxx/pqxx>
#include "headers/utils.h"
#include <iostream>

std::string get_groups(std::map<std::string, std::string> env, PostgresDB& db){
	try{
		std::string filename = "get_study_groups.sql";
		std::string sql = read_sql_file(env, filename);
		pqxx::result groups = db.execute(sql);
		if(!groups.empty()){
			json json_groups = result_to_json(groups);
			return json_groups.dump(4);
		}
		else{
			std::cerr << "List of groups is empty!"<< std::endl;
		}
	} catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        throw;
    }
}
