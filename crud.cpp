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
							 pqxx::params params){
	try{
		std::string sql = read_file(env["SQL_PATH"] + filename);
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


