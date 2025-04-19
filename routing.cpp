#include "headers/routing.h"
#include "headers/httplib.h"
#include "headers/crud.h"
#include "headers/db.h"
#include <string>


void base(httplib::Server& server){
	server.Get("/hi", [](const httplib::Request& req, httplib::Response& res) {
    res.set_content("Hello World!", "text/plain");
  	});
}

void get_groups(httplib::Server& server,
				std::map<std::string, std::string>& env,
				PostgresDB& db){
	std::string groups = get_data_from_db(env, db, "get_study_groups.sql", {});
	server.Get("/groups", [groups](const httplib::Request& req, httplib::Response& res) {
    res.set_content(groups, "application/json");
  	});
}

void create_server(std::map<std::string, std::string>& env, PostgresDB& db){
	httplib::Server server;
	//server.set_thread_pool_size(std::stoi(env["API_POOL_SIZE"])); //пул из 12 воркеров
	base(server);
  	get_groups(server, env, db);
  	server.set_mount_point("/", "./static");
  	std::cout << "Server running at http://localhost:8080\n";
  	server.listen(env["API_HOST"], std::stoi(env["API_PORT"]));
}