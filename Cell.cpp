#include <iostream>
#include <glut.h>

#include "Cell.h"
#include "Colors.h"

Cell::Cell(size_t max_level) :level(0), max_level(max_level), birthday(0){
	this->color = Colors::White;
}

Cell::Cell(size_t max_level, size_t level) : level(level), max_level(max_level), birthday(0){
	if (level > max_level)
		throw std::out_of_range("Exceeded the maximum level of cells");

	this->color = Colors::White;
}

void Cell::set_birthday(size_t birthday){
	this->birthday = birthday;
	this->set_color();
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
	if (this->is_alive())
		for (size_t i = 0; i < this->level; i++)
			this->draw_block(x, y, i);
}

void Cell::draw_block(size_t x, size_t y, int hight)const{
	this->color();

	glBegin(GL_QUADS);
	glVertex3f(x + 0.1, y + 0.1, hight);
	glVertex3f(x + 0.1, y + 0.1, hight + 1);
	glVertex3f(x + 0.9, y + 0.1, hight + 1);
	glVertex3f(x + 0.9, y + 0.1, hight);

	glVertex3f(x + 0.9, y + 0.1, hight);
	glVertex3f(x + 0.9, y + 0.1, hight + 1);
	glVertex3f(x + 0.9, y + 0.9, hight + 1);
	glVertex3f(x + 0.9, y + 0.9, hight);

	glVertex3f(x + 0.9, y + 0.9, hight);
	glVertex3f(x + 0.9, y + 0.9, hight + 1);
	glVertex3f(x + 0.1, y + 0.9, hight + 1);
	glVertex3f(x + 0.1, y + 0.9, hight);

	glVertex3f(x + 0.1, y + 0.1, hight);
	glVertex3f(x + 0.1, y + 0.1, hight + 1);
	glVertex3f(x + 0.1, y + 0.9, hight + 1);
	glVertex3f(x + 0.1, y + 0.9, hight);

	glVertex3f(x + 0.1, y + 0.1, hight);
	glVertex3f(x + 0.1, y + 0.9, hight);
	glVertex3f(x + 0.9, y + 0.9, hight);
	glVertex3f(x + 0.9, y + 0.1, hight);
	glEnd();

	glColor3ub(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(x + 0.1, y + 0.1, hight);
	glVertex3f(x + 0.9, y + 0.1, hight);

	glVertex3f(x + 0.9, y + 0.1, hight);
	glVertex3f(x + 0.9, y + 0.9, hight);

	glVertex3f(x + 0.9, y + 0.9, hight);
	glVertex3f(x + 0.1, y + 0.9, hight);

	glVertex3f(x + 0.1, y + 0.9, hight);
	glVertex3f(x + 0.1, y + 0.1, hight);

	glVertex3f(x + 0.9, y + 0.1, hight);
	glVertex3f(x + 0.9, y + 0.1, hight + 1);

	glVertex3f(x + 0.9, y + 0.9, hight);
	glVertex3f(x + 0.9, y + 0.9, hight + 1);

	glVertex3f(x + 0.1, y + 0.9, hight);
	glVertex3f(x + 0.1, y + 0.9, hight + 1);

	glVertex3f(x + 0.1, y + 0.1, hight);
	glVertex3f(x + 0.1, y + 0.1, hight + 1);

	glVertex3f(x + 0.1, y + 0.1, hight + 1);
	glVertex3f(x + 0.9, y + 0.1, hight + 1);

	glVertex3f(x + 0.9, y + 0.1, hight + 1);
	glVertex3f(x + 0.9, y + 0.9, hight + 1);

	glVertex3f(x + 0.9, y + 0.9, hight + 1);
	glVertex3f(x + 0.1, y + 0.9, hight + 1);

	glVertex3f(x + 0.1, y + 0.9, hight + 1);
	glVertex3f(x + 0.1, y + 0.1, hight + 1);
	glEnd();
	glLineWidth(1);
}

void Cell::set_color(){
	switch (this->birthday % 10)
	{
	case 0:
		this->color = Colors::LightGreen;
		break;
	case 1:
		this->color = Colors::Green;
		break;
	case 2:
		this->color = Colors::DarkGreen;
		break;
	case 3:
		this->color = Colors::LightBlue;
		break;
	case 4:
		this->color = Colors::Blue;
		break;
	case 5:
		this->color = Colors::DarkBlue;
		break;
	case 6:
		this->color = Colors::Yellow;
		break;
	case 7:
		this->color = Colors::Orange;
		break;
	case 8:
		this->color = Colors::Red;
		break;
	case 9:
		this->color = Colors::DarkRed;
		break;
	}
}