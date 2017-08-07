#include "Fstream.h"
#include "Coordinate.h"
#include "Debug.h"
#include <algorithm>
#include <iterator>
#include <limits>
#include <sstream>

using std::count;
using std::string;
using std::getline;
using std::istreambuf_iterator;
using std::vector;
using std::numeric_limits;
using std::ios_base;
using std::noskipws;
using std::map;
using std::for_each;
using std::make_pair;

//to delete
#include "Iostream.h"

/* we required a txt file to perform file operations on */
Fstream::Fstream(const std::string & txtFile):
	ifstream(txtFile),
	txtFile{txtFile} {
	/* spaces are allowed in the map. Also note this means
	we no longer skip newlines */
	ifstream >> noskipws;
}

Fstream::~Fstream() {}

/* counts the number of columns in the first line of a txt file by
counting the number of characters */
int Fstream::firstLineLength(void) {
	returnToFileBeginning();

	string firstLine;
	getline(ifstream, firstLine);
	return static_cast <int> (firstLine.length());
}

//counts the number of rows in a txt file by occurences of '\n'
int Fstream::numLines(void) {
	returnToFileBeginning(); //set the next character to read as the first character in the file

	return static_cast <int> (count ( //the static cast is just to silence warnings
		istreambuf_iterator <char>(ifstream), 
		istreambuf_iterator <char>(), //empty brackets means search until EOF
		'\n') + 1); //add 1 because our txt file's last line doesn't contain '\n'
}

/* Reads a rectangular section of the file with dimensions based on the 
num of lines in the file and the number of characters in the first line. Indeed,
since the map is rectangular this should work to read in the contents of
the ENTIRE map. */
std::vector <std::vector <char>> Fstream::readRectContent(void) {
	vector <vector <char>> content;
	int linesToRead = numLines();
	int charsToRead = firstLineLength();
	
	returnToFileBeginning();

	for (int i = 0; i < linesToRead; i++) {
		vector <char> line;
		line.reserve(charsToRead);

		for (int j = 0; j < charsToRead; j++) {
			char toRead;
			ifstream >> toRead;

			/* Since we don't skip whitespace, when we encounter a newline, read
			in the character as normal but do nothing with it. Then set the loop to
			iterate an additional time to read in the "real" character */
			if (toRead == '\n') {
				j -= 1;
				continue;
			}
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

	returnToFileBeginning();

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

/* Finds the coordinates of a set of characters in the txt file. Note
the enemy finder tool achieves the same thing. Use that instead. */
void Fstream::findCharOccurences(const vector <char> & keys) {
	map <const char, const Coordinate> charOccursAt; //a map storing known character locations
	Coordinate locationInFile{ 0, 0 }; //our current location in the file
	string line;
	returnToFileBeginning();

	while (getline(ifstream, line)) { //go through every line of the file
		for (const auto c : line) { //go through every character in a line
			/* Check if the character is in our list of keys, add the location of
			the character to our map if so */
			for_each(
				keys.begin(),
				keys.end(),
				[&charOccursAt, c, &locationInFile](char key) {
				if (c == key) charOccursAt.emplace(c, locationInFile); }
			);
			locationInFile.x++; //keep track of where we are in the file
		}

		/* keep tracks of where we are in the file */
		locationInFile.x = 0;
		locationInFile.y++;
	}

	/* Write the location to debug. Idea: write instead to an enemy file
	which we can then read from the enemy class. If the file is empty write
	a message asking to populate the file (i.e. run this function) first */
	for (auto m : charOccursAt) {
		std::stringstream ss;

		ss << m.first << " x: " << m.second.x << " y: " << m.second.y;
		string message = ss.str();
		Debug::write(message);
	}

}

//Sets the next character to read from the stream as the first character in the file
void Fstream::returnToFileBeginning(void) {
	ifstream.seekg(0);
}
