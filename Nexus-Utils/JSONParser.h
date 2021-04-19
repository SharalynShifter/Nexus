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

	void setBool(char* path, char* key, char* value);
	void setDouble(char* path, char* key, char* value);
	void setFloat(char* path, char* key, char* value);
	void setInt(char* path, char* key, char* value);
	void setString(char* path, char* key, char* value);

	Json::Value getJson(char* path);
	void writeJson(char* path, char* json);
};