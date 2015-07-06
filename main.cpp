#include <iostream>

#include "Life.h"

int main(int argc, char** argv){
	Life game(100,140,6);

	game.start_game(argc,argv);

	return 0;
}