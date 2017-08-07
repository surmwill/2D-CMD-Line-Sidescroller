#pragma once
#include <string>

class Error
{
	std::string message;

public:
	Error(const std::string & message);
	~Error();

	std::string getMessage(void);
};

