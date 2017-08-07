#include "Error.h"

using std::string;

Error::Error(const std::string & message) : message{ message } {}


Error::~Error()
{
}

string Error::getMessage(void) {
	return message;
}


