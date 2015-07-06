#pragma once

#include "Field.h"

#ifndef GAME_OF_LIFE_LIFE_H
#define GAME_OF_LIFE_LIFE_H

class Life{
public:
	Life(size_t size_x, size_t size_y, size_t max_level);

	void start_game(int argc, char** argv);
private:
	Field field;

	static Life* static_this;

	void init_gl();
	static void draw_game();
	static void timer_game(int);
};

#endif