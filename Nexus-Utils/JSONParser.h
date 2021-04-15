#pragma once
#include <string>

class __declspec(dllexport) JSONParser
{
public:
	std::string read(char* file);
};

