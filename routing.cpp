#include "headers/routing.h"
#include "headers/httplib.h"
#include "headers/crud.h"
#include "headers/db.h"
#include "headers/utils.h"
#include <string>
#include <pqxx/pqxx>

void set_headers(httplib::Response& res, std::string method){
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", method);
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.set_header("Content-Type", "application/json");
}

void base_page(httplib::Server& server, std::string endpoint, std::string filename){
    server.Get("/" + endpoint, [filename](const httplib::Request& req, httplib::Response& res) {
        std::string html = read_file(filename);
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

void get_disciplines(httplib::Server& server,
                std::map<std::string, std::string>& env,
                PostgresDB& db){
    server.Get("/get_discs", [&](const httplib::Request& req, httplib::Response& res) {
        std::string discs = exec_sql(env, db, "get_discs.sql", {});
        set_headers(res, "GET");
        res.set_content(discs, "application/json");
    });
}

void get_students(httplib::Server& server,
                std::map<std::string, std::string>& env,
                PostgresDB& db){
    server.Get("/get_students", [&](const httplib::Request& req, httplib::Response& res) {
        std::string students = exec_sql(env, db, "get_students.sql", {});
        set_headers(res, "GET");
        res.set_content(students, "application/json");
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
    	pqxx::params res_params;
        res_params.append(group_name);
        res_params.append(group_semester);
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

void add_student(httplib::Server& server,
                std::map<std::string, std::string>& env,
                PostgresDB& db){
    server.Post("/add_student", [&](const httplib::Request& req, httplib::Response& res) {
        try{
        json request_data = json::parse(req.body);
        pqxx::params res_params, group_name_param;
        int group_id = request_data["group_id"];
        res_params.append(clear_string(request_data["name"].dump()));
        res_params.append(clear_string(request_data["lastname"].dump()));
        res_params.append(clear_string(request_data["patronymic"].dump()));
        res_params.append(clear_string(request_data["birthdate"].dump()));
        res_params.append(group_id);
        res_params.append(clear_string(request_data["gender"].dump()));
        std::string result = exec_sql(env, db, "add_student.sql", res_params);
        set_headers(res, "POST");
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

void add_discipline(httplib::Server& server,
                std::map<std::string, std::string>& env,
                PostgresDB& db){
    server.Post("/add_disc", [&](const httplib::Request& req, httplib::Response& res) {
        try{
        json request_data = json::parse(req.body);
        std::string disc_name = request_data["disc_name"];
        int hours_amount = request_data["hours_amount"];
        std::string attestation_type = request_data["attestation_type"];
        pqxx::params attest_params;
        attest_params.append(attestation_type);
        std::string attest_pk_res = exec_sql(env, db, "get_attest_pk_by_name.sql", attest_params);
        json attest_pk_json = json::parse(attest_pk_res);
        std::string attest_pk = attest_pk_json[0]["pk"];
        pqxx::params res_params;
        res_params.append(disc_name);
        res_params.append(hours_amount);
        res_params.append(std::stoi(attest_pk));
        std::string result = exec_sql(env, db, "add_disc.sql", res_params);
        set_headers(res, "POST");
            res.set_content(
                json{{"status", "success"}, {"discipline", disc_name}}.dump(),
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
        pqxx::params res_params;
        res_params.append(group_id);
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

void delete_discipline(httplib::Server& server, std::map<std::string, std::string>& env, PostgresDB& db){
    server.Delete("/delete_disc", [&](const httplib::Request& req, httplib::Response& res) {
        try {
        json request_data = json::parse(req.body);
        int disc_id = request_data["pk"];
        pqxx::params res_params;
        res_params.append(disc_id);
        exec_sql(env, db, "delete_vedomost_by_disc.sql", res_params);
        exec_sql(env, db, "delete_disc.sql", res_params);
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

void delete_student(httplib::Server& server, std::map<std::string, std::string>& env, PostgresDB& db){
    server.Delete("/delete_student", [&](const httplib::Request& req, httplib::Response& res) {
        try {
        json request_data = json::parse(req.body);
        int stud_id = request_data["pk"];
        pqxx::params res_params;
        res_params.append(stud_id);
        exec_sql(env, db, "delete_vedomost_by_student.sql", res_params);
        exec_sql(env, db, "delete_student.sql", res_params);
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
    base_page(server, "groups", "static/groups.html");
    base_page(server, "disciplines", "static/discipline.html");
    base_page(server, "students", "static/students.html");
    get_groups(server, env, db);
    get_disciplines(server, env, db);
    get_students(server, env, db);
    add_group(server, env, db);
    add_discipline(server, env, db);
    add_student(server, env, db);
    delete_group(server, env, db);
    delete_discipline(server, env, db);
    delete_student(server, env, db);
    server.set_mount_point("/static", "./static");
    server.listen(env["API_HOST"], std::stoi(env["API_PORT"]));
}