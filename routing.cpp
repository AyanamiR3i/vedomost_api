#include "headers/routing.h"
#include "headers/httplib.h"
#include "headers/crud.h"
#include "headers/db.h"
#include "headers/utils.h"
#include <string>

void set_headers(httplib::Response& res, std::string method){
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", method);
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.set_header("Content-Type", "application/json");
}

void base_groups(httplib::Server& server){
    server.Get("/groups", [](const httplib::Request& req, httplib::Response& res) {
        std::string html = read_file("static/groups.html");
        if(html.empty()){
            res.status = 404;
            res.set_content("Page not found", "text/plain");
            return;
        }
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(html,  "text/html; charset=utf-8");
    });
}

void get_groups(httplib::Server& server,
                std::map<std::string, std::string>& env,
                PostgresDB& db){
    server.Get("/get_groups", [&](const httplib::Request& req, httplib::Response& res) {
        std::string groups = exec_sql(env, db, "get_study_groups.sql", {});
        set_headers(res, "GET");
        res.set_content(groups, "application/json");
    });
}

void add_group(httplib::Server& server,
                std::map<std::string, std::string>& env,
                PostgresDB& db){
    server.Post("/add_group", [&](const httplib::Request& req, httplib::Response& res) {
    	try{
    	json request_data = json::parse(req.body);
    	std::string group_name = request_data["name"];
    	short group_semester = request_data["semester"];
    	std::vector<PostgresDB::params> res_params;
        res_params.push_back(PostgresDB::params());
        res_params[0].string_param = group_name;
        res_params.push_back(PostgresDB::params());
        res_params[1].string_param = std::to_string(group_semester);
        std::string result = exec_sql(env, db, "add_group.sql", res_params);
        set_headers(res, "POST");
            res.set_content(
                json{{"status", "success"}, {"group", group_name}}.dump(),
                "application/json"
            );
    } 
	catch (const std::exception& e){
		res.status = 400;
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(
            json{{"status", "error"}, {"message", e.what()}}.dump(),
            "application/json"
        );
	}});
}

void delete_group(httplib::Server& server, std::map<std::string, std::string>& env, PostgresDB& db){
    server.Delete("/delete_group", [&](const httplib::Request& req, httplib::Response& res) {
        try {
        json request_data = json::parse(req.body);
        int group_id = request_data["pk"];
        std::vector<PostgresDB::params> res_params;
        res_params.push_back(PostgresDB::params());
        res_params[0].int_param = group_id;
        exec_sql(env, db, "delete_vedomost_by_group.sql", res_params);
        exec_sql(env, db, "delete_students_by_group.sql", res_params);
        exec_sql(env, db, "delete_group.sql", res_params);
        set_headers(res, "DELETE");
            res.set_content(
                json{{"status", "success"}}.dump(),
                "application/json"
            );
    } 
    catch (const std::exception& e){
        res.status = 400;
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(
            json{{"status", "error"}, {"message", e.what()}}.dump(),
            "application/json"
        );
    }});
}

void create_server(std::map<std::string, std::string>& env, PostgresDB& db){
    httplib::Server server;
    base_groups(server);
    get_groups(server, env, db);
    add_group(server, env, db);
    delete_group(server, env, db);
    server.set_mount_point("/static", "./static");
    server.listen(env["API_HOST"], std::stoi(env["API_PORT"]));
}