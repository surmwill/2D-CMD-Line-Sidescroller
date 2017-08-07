#include "Debug.h"

using std::string;
using std::ofstream;
using std::to_string;

ofstream Debug::ofs{ "Debug.txt" };

Debug::Debug()
{
}


Debug::~Debug()
{
}

void Debug::write(const string & message) {
	ofs << message << '\n';
}

void Debug::write(const int num) {
	ofs << to_string(num) << '\n';
}
