#pragma once

#include "Field.h"

#ifndef GAME_OF_LIFE_LIFE_H
#define GAME_OF_LIFE_LIFE_H

class Life{
public:
	Life(size_t width, size_t height, size_t size, size_t max_level, bool view_3d);
	Life(const char* file_name);

	void start_game(int argc, char** argv);
	void start_game(int argc, char** argv,size_t probability);
private:
	Field field;

	size_t width;
	size_t height;

	int angle_z;
	int angle_y;

	static Life* static_this;

	void(*view_func)();


	void init_gl();

	static void init_2d();
	static void init_3d();

	static void special_keyboard(int key, int x, int y);
	static void draw_game();
	static void timer_game(int);
};

#endif