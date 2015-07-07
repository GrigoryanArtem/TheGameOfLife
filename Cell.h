#pragma once

#ifndef GAME_OF_LIFE_CELL_H
#define GAME_OF_LIFE_CELL_H

class Cell{
public:
	Cell(size_t max_level);
	Cell(size_t max_level,size_t level);

	void set_birthday(size_t birthday);

	bool increase() _NOEXCEPT;
	bool reduce() _NOEXCEPT;
	bool is_alive() const _NOEXCEPT;
	void kill();

	size_t get_level()const _NOEXCEPT;

	void draw(size_t x, size_t y)const _NOEXCEPT;
private:
	size_t level;
	size_t max_level;
	size_t birthday;

	void(*color)();

	void draw_block(size_t x, size_t y, int hight)const;
	void set_color();
};

#endif