#include "pch.h"
#include "JSONParser.h"
#include <fstream>
#pragma warning(disable : 4996)

bool JSONParser::getBool(char* path, char* key) {
	std::ifstream file(path);
	Json::Value json;
	Json::Reader reader;

	reader.parse(file, json);

	return json[key].asBool();
}

double JSONParser::getDouble(char* path, char* key) {
	std::ifstream file(path);
	Json::Value json;
	Json::Reader reader;

	reader.parse(file, json);

	return json[key].asDouble();
}

float JSONParser::getFloat(char* path, char* key) {
	std::ifstream file(path);
	Json::Value json;
	Json::Reader reader;

	reader.parse(file, json);

	return json[key].asFloat();
}

int JSONParser::getInt(char* path, char* key) {
	std::ifstream file(path);
	Json::Value json;
	Json::Reader reader;

	reader.parse(file, json);
	
	return json[key].asInt();
}

std::string JSONParser::getString(char* path, char* key) {
	std::ifstream file(path);
	Json::Value json;
	Json::Reader reader;

	reader.parse(file, json);

	return json[key].asString();
}

Json::Value JSONParser::getJson(char* path) {
	std::ifstream file(path);
	Json::Value json;
	Json::Reader reader;

	reader.parse(file, json);

	return json;
}