#pragma once
#include <memory>
#include <vector>
#include <Windows.h>
#include <string>

//to delete
#include <fstream>

struct DisplayImpl;
struct Coordinate;

class Display final {
	std::unique_ptr <DisplayImpl> displayImpl;
	std::ofstream ofs{ "Debug.txt" };

	void updateCursorPos(const int numWrites);
	void writeConsole(const WCHAR toWrite, const DWORD length);
	void writeStringToConsole(const std::string strToWrite, bool slowType = false);
	void setConsoleDimensions(void);
	void setConsoleProperties(void);
	void disableConsoleCursor(void);
	void clearDialogue(void);
	void nextDrawPosition(const int row, const int col);
	void adjustTextProperties(void);
	void drawUI(void);

public:
	Display();
	~Display();

	void drawMap(
		std::vector <std::vector <char>> & newTiles
	);

	void drawDialogue(
		const int line, 
		const std::string name, 
		const std::string dialogue,
		bool slowType = true);
};

