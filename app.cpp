//инстанс приложения
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <pqxx/pqxx>
#include "headers/init.h"
#include "headers/db.h"



pqxx::connection get_session(){

}

int main(){
	InitApp app = InitApp();
	std::map<std::string, std::string> env = app.get_app_env(app.get_env_value());
	pqxx::connection session = get_session(env);
	if(session.is_open()){
		std::cout<<"Все гуд"<<std::endl;
	}
	else{
		std::cout<<"Подключение умерло"<<std::endl;
	}
	return 0;
}
