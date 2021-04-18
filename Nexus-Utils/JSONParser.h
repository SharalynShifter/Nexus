#pragma once
#include <json/value.h>
#include <json/json.h>
#include <string>

class __declspec(dllexport) JSONParser
{
public:
	bool getBool(char* path, char* key);
	double getDouble(char* path, char* key);
	float getFloat(char* path, char* key);
	int getInt(char* path, char* key);
	std::string getString(char* path, char* key);

	Json::Value getJson(char* path);
};