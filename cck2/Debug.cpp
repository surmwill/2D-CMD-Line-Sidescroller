#include "Debug.h"

using std::string;
using std::ofstream;

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
