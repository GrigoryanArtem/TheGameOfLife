#pragma once

#ifndef GAME_OF_LIFE_CELL_H
#define GAME_OF_LIFE_CELL_H

class Cell{
public:
	Cell(size_t max_level) :level(0), max_level(max_level){}
	Cell(size_t level, size_t max_level);

	bool increase() _NOEXCEPT;
	bool reduce() _NOEXCEPT;
	bool is_alive() const _NOEXCEPT;
	void kill();

	size_t get_level()const _NOEXCEPT;

	void draw()const _NOEXCEPT;
private:
	size_t level;
	size_t max_level;
};

#endif