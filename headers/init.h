//InitApp.h
#ifndef INIT_APP_H
#define INIT_APP_H
#include <map>
#include <cstdlib>
#include <iostream>
class InitApp{
	private:
		const char* env_name = "APP_ENV";
		const char* env_value = getenv(env_name);
	public:
		const char* get_env_value();
		std::map<std::string, std::string> get_app_env(const char* env_value);
};
#endif //INIT_APP_H


