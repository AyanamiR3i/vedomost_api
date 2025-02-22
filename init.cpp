//файл инициализации приложения
#include "headers/init.h"
#include <iostream>
#include <cstdlib> 
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include "headers/utils.h"
using namespace std;

const char* InitApp::get_env_value(){
			return env_value;
}
map<string, string> InitApp::get_app_env(const char* env_value){
	// получение переменных окружения и запись в map
	if (env_value != nullptr){
        char delimiter = ';';
		char key_value_delimiter = '=';
		map<string, string> env_map;
		vector<string> pairs = split(env_value, delimiter);
		for (const string& pair : pairs) {
        	vector<string> key_value = split(pair, key_value_delimiter);

	        if (key_value.size() == 2) {
	            string key = key_value[0];
	            string value = key_value[1];
	            env_map[key] = value;
	        	}
    	}
    return env_map;
	}
	else{
		map<string, string> empty_map{};
		return empty_map;
	}
}
