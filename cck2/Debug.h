#pragma once
#include <fstream>
#include <string>

class Debug
{
	static std::ofstream ofs;
public:
	Debug();
	~Debug();
	static void write(const std::string & message);
};

