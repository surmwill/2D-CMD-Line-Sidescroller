#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <algorithm>

using namespace std;

struct Coordinate {
	Coordinate(const int x, const int y) : x{ x }, y{ y } {};
	int x;
	int y;
};


int main() {
	int charNum = 1;
	char input;
	string fileName;
	string filePath;
	vector <char> keys;

	cout << "name of the file are we working on? (don't include .txt!) : ";
	cin >> fileName;

	// All level designs will be kept in the Level folder
	filePath = "..\\..\\..\\Levels\\" + fileName + ".txt";
	ifstream ifs(filePath);

	// Check we can actually open the file
	if (!ifs.good()) {
		cout << "could not open " << filePath << endl;
		return -1;
	}

	// Take input for what characters we are searching for
	cout << "find occurences of the following characters (ctrl + z + enter to stop input): " << endl;
	while (1) {
		cout << "character " << charNum << ": ";
		cin >> input;

		if (cin.good()) keys.emplace_back(input);
		else break;

		charNum++;
	}

	map <const char, const Coordinate> charOccursAt; //a map storing known character locations
	Coordinate locationInFile{ 0, 0 }; //our current location in the file
	string line;

	while (getline(ifs, line)) { // go through every line of the file
		for (const auto c : line) { // go through every character in a line
			/* Check if the character is in our list of keys,
			if so, add the location of the character to our map */
			for_each(
				keys.begin(),
				keys.end(),
				[&charOccursAt, c, &locationInFile](char key) {
				if (c == key) charOccursAt.emplace(c, locationInFile); }
			);

			locationInFile.x++; // keep track of where we are in the file
		}

		/* keep track of where we are in the file */
		locationInFile.x = 0;
		locationInFile.y++;
	}

	// All enemy coordinate will be kept in the EnemyInfo folder
	filePath = "..\\..\\..\\EnemyInfo\\" + fileName + ".txt";
	ofstream ofs{ filePath };

	// Check we can open the file
	if (!ofs.good()) {
		cout << "could not open " << filePath << endl;
		return -1;
	}

	/* Write the coordinates of the found characters to the file,
	as well as what the character is */
	for (auto m : charOccursAt) {
		std::stringstream ss;

		ss << m.first << " x: " << m.second.x << " y: " << m.second.y;
		string message = ss.str();
		ofs << message << '\n';
	}
}

