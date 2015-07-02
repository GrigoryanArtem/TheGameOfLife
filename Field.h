#pragma once

#ifndef GAME_OF_LIFE_FIELD_H
#define GAME_OF_LIFE_FIELD_H

class Field{
public:
	Field(size_t size_x, size_t size_y) :size_x(size_x), size_y(size_y), count(0){}

	void draw() const;

	size_t get_count() const;
private:
	size_t size_x;
	size_t size_y;

	size_t count;
};

#endif