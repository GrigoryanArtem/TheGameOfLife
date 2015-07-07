#pragma once

#ifndef GAME_OF_LIFE_FIELD_H
#define GAME_OF_LIFE_FIELD_H

#include <vector>

#include "Cell.h"

class Field{
public:
	Field(size_t size_x, size_t size_y, size_t max_cell_level) :size_x(size_x), size_y(size_y), count(0), ticks(0),
		max_cell_level(max_cell_level), field(size_x + 2, std::vector<Cell>(size_y + 2, Cell(max_cell_level))){}

	void draw() const;

	size_t get_count() const _NOEXCEPT;
	size_t get_size_x() const _NOEXCEPT;
	size_t get_size_y() const _NOEXCEPT;

	void generate();
	void make_step();

	void select(size_t x, size_t y);
	void unselect(size_t x, size_t y);
private:
	size_t size_x;
	size_t size_y;
	size_t count;
	size_t ticks;

	size_t max_cell_level;

	std::vector<std::vector<Cell> > field;

	size_t number_of_living_cells(size_t x, size_t y)const;
};

#endif