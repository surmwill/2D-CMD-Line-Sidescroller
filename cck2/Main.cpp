#include <iostream>
#include "CmdInterpreter.h"


//add explicits to constructors

/* headers that allows _CrtDumpMemoryLeaks(); to check 
/ for memory leaks */
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

//to delete
#include "Map.h"
#include <fstream>
#include <string>

void runTowers(void) {
	CmdInterpreter cmd;
	
	std::cout << "Press any key to exit";
	std::cin.get();
}

int main(void) {
	runTowers();
	_CrtDumpMemoryLeaks(); //checks for memory leaks
}