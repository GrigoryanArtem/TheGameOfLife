#include <iostream>

#include "Life.h"

int main(int argc, char** argv){
	Life game(60,106,1); //60 106

	game.start_game(argc,argv);

	return 0;
}