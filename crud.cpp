//dml операции

#include "headers/crud.h"
#include <pqxx/pqxx>
#include "headers/utils.h"
#include <iostream>
#include <vector>

std::string get_data_from_db(std::map<std::string, std::string> env,							
							 PostgresDB& db,
							 std::string filename,
							 std::vector<std::string> vector_params){
	try{
		std::string sql = read_sql_file(env, filename);
		pqxx::params params;
		for(auto &p: vector_params){
			params.append(p);
		}
		pqxx::result data = db.execute(sql, params);
		if(!data.empty()){
			json json_result = result_to_json(data);
			return json_result.dump(4);
		}
		else{
			std::cerr << "List is empty!"<< std::endl;
		}
	} catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        throw;
    }
}


