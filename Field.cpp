#include <iostream>
#include <fstream>
#include <random>
#include <glut.h>

#include "Field.h"

Field::Field(const char* file_name){
	std::ifstream map(file_name);
	size_t sz_x, sz_y, mx_lvl; // sz - size, mx - max

	map >> sz_x >> sz_y >> mx_lvl;

	this->size_x = sz_x;
	this->size_y = sz_y;
	this->max_cell_level = mx_lvl;

	this->field = std::vector<std::vector<Cell> >(size_x + 2, std::vector<Cell>(size_y + 2, Cell(max_cell_level)));

	int temp;
	map >> temp;
	if (temp){
		this->generate(temp);
	}
	else{
		for (size_t i = 0; i < sz_x; i++){
			for (size_t k = 0; k < sz_y; k++){
				map >> temp;

				if (temp)
					this->select(sz_x - i - 1, k, temp);
			}
		}
	}

	map.close();
}

void Field::draw()const{
	for (size_t i = 1; i <= this->size_x; i++)
		for (size_t k = 1; k <= this->size_y; k++)
			this->field.at(i).at(k).draw(k, i);

	glColor3b(0, 0, 0);

	glBegin(GL_LINES);

	for (size_t i = 1; i <= this->size_x + 1; i++){
		glVertex3f(1, i, 0);
		glVertex3f(this->size_y + 1, i, 0);
	}

	for (size_t i = 1; i <= this->size_y + 1; i++){
		glVertex3f(i, 1, 0);
		glVertex3f(i, this->size_x + 1, 0);
	}

	glEnd();
}

size_t Field::get_count()const{
	return this->count;
}

size_t Field::get_size_x() const{
	return this->size_x;
}

size_t Field::get_size_y() const{
	return this->size_y;
}

size_t Field::number_of_living_cells(size_t x, size_t y)const{
	size_t count(0);

	for (size_t i = x - 1; i <= x + 1; i++)
		for (size_t k = y - 1; k <= y + 1; k++)
			if (this->field.at(i).at(k).is_alive())
				count++;

	return (this->field.at(x).at(y).is_alive() ? count - 1 : count);
}

void Field::generate(size_t probability){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 100);

	for (size_t i = 1; i < this->field.size() - 1; i++)
		for (size_t k = 1; k < this->field.at(i).size() - 1; k++)
			this->field[i][k] = Cell(this->max_cell_level, (int)probability < dist(gen) ? 1 : 0);
}

void Field::make_step(){
	std::vector<std::vector<Cell> > temp(size_x + 2, std::vector<Cell>(size_y + 2, Cell(this->max_cell_level)));

	this->ticks++;

	for (size_t i = 1; i < this->field.size() - 1; i++){
		for (size_t k = 1; k < this->field.at(i).size() - 1; k++){
			temp[i][k] = this->field[i][k];

			if (this->field[i][k].is_alive()){

				if (this->number_of_living_cells(i, k) == 0 || this->number_of_living_cells(i, k) >= 6)
					temp[i][k].reduce();

				if (this->number_of_living_cells(i, k) == 2 || this->number_of_living_cells(i, k) == 3)
					temp[i][k].increase();

				if (this->number_of_living_cells(i, k) == 1 || (this->number_of_living_cells(i, k) >= 4 && this->number_of_living_cells(i, k) <= 5))
					temp[i][k].kill();
			}
			else{
				if (this->number_of_living_cells(i, k) == 3){
					temp[i][k].increase();
					temp[i][k].set_birthday(this->ticks);
				}
			}
		}
	}

	this->field = temp;
}

void Field::select(size_t x, size_t y){
	if (x > this->size_x || y > this->size_y)
		throw std::out_of_range("out");

	this->field[x + 1][y + 1] = Cell(this->max_cell_level, 1);
}

void Field::select(size_t x, size_t y, size_t level){
	if (x > this->size_x || y > this->size_y)
		throw std::out_of_range("out");

	this->field[x + 1][y + 1] = Cell(this->max_cell_level, level);
}