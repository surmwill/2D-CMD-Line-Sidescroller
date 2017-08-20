#pragma once
#include <memory>
#include <vector>
#include <Windows.h>
#include <string>

//to delete
#include <fstream>

struct DisplayImpl;
struct Coordinate;
class DisplayCommands;

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
	void setNextDrawPosition(const int row, const int col = 0);
	void adjustTextProperties(void);
	void drawUI(void);
	void waitForSpacePressToClear(void);

public:
	Display(std::unique_ptr <DisplayCommands> cmd);
	~Display();

	void drawMap(
		std::vector <std::vector <char>> & newTiles
	);

	void drawDialogue(
		const std::string & name, 
		const std::string & dialogue,
		const int line = 0,
		const int indent = 0,
		bool batchWrite = false,
		bool slowType = true);

	void drawOptions(const std::vector <std::string> options);

	int mapWidth(void);
	int mapHeight(void);
};

