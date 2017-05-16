#include "Fstream.h"
#include <algorithm>
#include <iterator>
#include <limits>

using std::count;
using std::string;
using std::getline;
using std::istreambuf_iterator;
using std::vector;
using std::numeric_limits;
using std::ios_base;

//to delete
#include "Iostream.h"

/* we required a txt file to perform file operations on */
Fstream::Fstream(const std::string & txtFile):
	ifstream(txtFile),
	txtFile{txtFile} {}

Fstream::~Fstream() {}

/* counts the number of columns in the first line of a txt file by
counting the number of characters */
int Fstream::firstLineLength(void) {
	ifstream.seekg(0);
	string firstLine;
	getline(ifstream, firstLine);
	return firstLine.length();
}

//counts the number of rows in a txt file by occurences of '\n'
int Fstream::numLines(void) {
	ifstream.seekg(0); //iterator to the beginning of the filestream
	return count(
		istreambuf_iterator <char>(ifstream), 
		istreambuf_iterator <char>(), //empty brackets means search until EOF
		'\n') + 1; //add 1 because our txt file's last line doesn't contain '\n'
}

/* Reads a rectangular section of the file with dimensions based on the 
num of lines in the file and the number of characters in the first line. Indeed,
since the map is rectangular this should work to read in the contents of
the ENTIRE map. */
std::vector <std::vector <char>> Fstream::readRectContent(void) {
	vector <vector <char>> content;
	int linesToRead = numLines();
	int charsToRead = firstLineLength();
	ifstream.seekg(0);

	for (int i = 0; i < linesToRead; i++) {
		vector <char> line;
		line.reserve(charsToRead);

		for (int j = 0; j < charsToRead; j++) {
			char toRead;
			ifstream >> toRead;
			line.insert(line.end(), toRead);
		}
		content.emplace_back(line);
	}

	return content;
}

/* Reads a specific rectangular section of a txt file. This allows
us to display sections of the map, instead of the entire thing. Note 
this fn has been replaced by the Map function updateVisibleArea. UpdateVisibleArea
accomplishes the same task by first reading the entire map into a vector,
then reading a block from the vector, forgoing the constant file reading */
vector <vector <char>> Fstream::readTxTBlock(
	const int fromChar,
	const int charsToRead,
	const int startLine,
	const int linesToRead) {
	vector <vector <char>> block;
	vector <char> line;
	ifstream.seekg(0);

	// skips to out desired starting line by ignoring startLine amount of '\n'
	for (int i = 0; i < startLine; i++) {
		ifstream.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}

	// reads charsToRead amount of characters from our desired lines
	for (int i = 0; i < linesToRead; i++) {
		//the next char to read is a fromChar offset from the current stream position 
		ifstream.seekg(fromChar, ios_base::cur); 
		for (int j = 0; j < charsToRead; j++) {
			char toRead;
			ifstream >> toRead;
			line.emplace_back(toRead);
		}

		block.emplace_back(line);
		line.clear();
		ifstream.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}

	return block;
}

