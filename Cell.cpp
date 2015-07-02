#include <iostream>
#include <glut.h>

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

void Cell::draw(size_t x, size_t y)const{
	if (this->is_alive()){
		glColor3f(0, 0, 0);

		glBegin(GL_QUADS);

		glVertex3f(x + 0.1, y + 0.1, 0);
		glVertex3f(x + 0.9, y + 0.1, 0);
		glVertex3f(x + 0.9, y + 0.9, 0);
		glVertex3f(x + 0.1, y + 0.9, 0);

		glEnd();
	}
}