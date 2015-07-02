#include <iostream>

#include "Cell.h"

Cell::Cell(size_t level, size_t max_level) : level(level), max_level(max_level){
	if (level > max_level)
		throw std::out_of_range("Exceeded the maximum level of cells");
}

bool Cell::increase(){
	if (this->level == this->max_level)
		return false;

	this->level++;
	return true;
}

bool Cell::reduce(){
	if (this->level == 0)
		return false;

	this->level--;
	return true;
}

void Cell::kill(){
	this->level = 0;
}

bool Cell::is_alive()const{
	return this->level != 0;
}

size_t Cell::get_level()const{
	return this->level;
}

void Cell::draw()const{
	if (this->level == 0)
		std::cout << ' ';
	else
		std::cout << this->level;
}