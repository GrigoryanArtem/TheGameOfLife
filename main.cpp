#include <iostream>

#include "Life.h"

int main(int argc, char** argv){
	Life game("game.config");
	//Life game(1280, 720, 130, 2, true);

	game.start_game(argc,argv);

	return 0;
}