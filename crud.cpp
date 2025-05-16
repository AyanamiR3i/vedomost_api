//dml операции

#include "headers/crud.h"
#include <pqxx/pqxx>
#include "headers/utils.h"
#include <iostream>
#include <vector>
#include "headers/db.h"

std::string exec_sql(std::map<std::string, std::string> env,							
							 PostgresDB& db,
							 std::string filename,
							 std::vector<PostgresDB::params> vector_params){
	try{
		std::string sql = read_file(env["SQL_PATH"] + filename);
		pqxx::params params;
		for(auto &p: vector_params){
			if(p.int_param != -1){
				params.append(p.int_param);
			}
			else if(p.double_param != -1.0){
				params.append(p.double_param);
			}
			else if (p.string_param != ""){
				params.append(p.string_param);
			}
		}
		pqxx::result data = db.execute(sql, params);
		db.commit();
		if(!data.empty()){
			json json_result = result_to_json(data);
			return json_result.dump(4);
		}
		else{
			return json{{"status", "success"}}.dump();
		}
	} catch (const std::exception& e) {
		db.rollback();
        std::cerr << "Exception caught: " << e.what() << std::endl;
        throw;
    }
}


