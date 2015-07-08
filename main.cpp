#include <iostream>
#include <Windows.h>

#include "Life.h"

int main(int argc, char** argv){
	Life game("game.config");

	FreeConsole();
	game.start_game(argc,argv,20);

	return 0;
}