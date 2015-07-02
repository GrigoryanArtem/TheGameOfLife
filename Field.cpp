#include <iostream>
#include <random>

#include "Field.h"

void Field::draw()const{
	for (size_t i = 1; i < this->field.size() - 1; i++){
		for (size_t k = 1; k < this->field.at(i).size() - 1; k++)
			this->field.at(i).at(k).draw();

		std::endl(std::cout);
	}
}

size_t Field::get_count()const{
	return this->count;
}


size_t Field::number_of_living_cells(size_t x, size_t y)const{
	size_t count(0);

	for (size_t i = x - 1; i <= x + 1; i++)
		for (size_t k = y - 1; k <= y + 1; k++)
			if (this->field.at(i).at(k).is_alive())
				count++;

	return (this->field.at(x).at(y).is_alive() ? count - 1 : count);
}

void Field::generate(){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1);

	for (size_t i = 1; i < this->field.size() - 1; i++)
		for (size_t k = 1; k < this->field.at(i).size() - 1; k++)
			this->field[i][k] = Cell(dist(gen) ,this->max_cell_level);
}

void Field::make_step(){
	std::vector<std::vector<Cell> > temp(size_x, std::vector<Cell>(size_y, Cell(this->max_cell_level)));

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
				if (this->number_of_living_cells(i, k) == 3)
					temp[i][k].increase();
			}
		}
	}

	this->field = temp;
}