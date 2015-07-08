#include <cstdlib>
#include <glut.h>
#include <fstream>
#include <iostream>
#include <string>

#include "Life.h"

const int PERSPECTIVE_CONST_X = 2;
const int PERSPECTIVE_CONST_Y = 4;
const int PERSPECTIVE_CONST_Z = 5;

Life *Life::static_this;

Life::Life(size_t width, size_t height, size_t size, size_t max_level, bool view_3d) : width(width), height(height), field(size, size, max_level),
	angle_y(45), angle_z(0){
	static_this = this;

	this->view_func = view_3d ? Life::init_3d : Life::init_2d;
}

Life::Life(const char* file_name){
	std::ifstream file("game.config");
	bool view_3d;
	std::string field_name;

	file >> this->width >> this->height >> view_3d;
	file >> field_name;
	this->view_func = view_3d ? Life::init_3d : Life::init_2d;
	this->field = Field(field_name.c_str());

	static_this = this;
}

void Life::start_game(int argc, char** argv, size_t probability){
	this->field.generate(probability);
	this->start_game(argc,argv);
}

void Life::start_game(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("<= Life by.GrigoryanArtem =>");

	this->init_gl();
	glutDisplayFunc(&Life::draw_game);
	glutSpecialFunc(&Life::special_keyboard);
	glutTimerFunc(50,&Life::timer_game,0);

	glutMainLoop();
}

void Life::init_gl(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	this->view_func();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Life::draw_game(){
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static_this->field.draw();

	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void Life::timer_game(int = 0){
	static_this->field.make_step();
	draw_game();
	glutTimerFunc(50, &Life::timer_game, 0);
}

void Life::init_2d(){
	glOrtho(0, static_this->field.get_size_y() + 2, 0, static_this->field.get_size_x() + 2, -100, 100);
}

void Life::init_3d(){
	gluPerspective(45, (float)1280 / 720, 1, 10000);
	glTranslatef(-(int)((static_this->field.get_size_y() + 2) / PERSPECTIVE_CONST_X), -(int)((static_this->field.get_size_x() + 2) / PERSPECTIVE_CONST_Y),
		-(int)((static_this->field.get_size_y() + 2) / 7 * PERSPECTIVE_CONST_Z));
	glRotatef(-45, 1, 0, 0);
}

void Life::special_keyboard(int key, int x, int y){
	switch (key){
	case GLUT_KEY_RIGHT:
		glTranslatef((int)((static_this->field.get_size_y() + 2) / PERSPECTIVE_CONST_X), (int)((static_this->field.get_size_x() + 2) / PERSPECTIVE_CONST_X),0);
		glRotatef(5, 0, 0, 1);
		glTranslatef( -(int)((static_this->field.get_size_y() + 2) / PERSPECTIVE_CONST_X), -(int)((static_this->field.get_size_x() + 2) / PERSPECTIVE_CONST_X), 0);
		static_this->angle_z+=5;
		break;
	case GLUT_KEY_LEFT:
		glTranslatef((int)((static_this->field.get_size_y() + 2) / PERSPECTIVE_CONST_X), (int)((static_this->field.get_size_x() + 2) / PERSPECTIVE_CONST_X), 0);
		glRotatef(-5, 0, 0, 1);
		glTranslatef(-(int)((static_this->field.get_size_y() + 2) / PERSPECTIVE_CONST_X), -(int)((static_this->field.get_size_x() + 2) / PERSPECTIVE_CONST_X), 0);
		static_this->angle_z -= 5;
		break;
	case GLUT_KEY_UP:
		glTranslatef(0, (int)((static_this->field.get_size_x() + 2) / PERSPECTIVE_CONST_X), 0);
		glRotatef(-static_this->angle_z, 0, 0, 1);
		glRotatef(5, 1, 0, 0);
		glRotatef(static_this->angle_z, 0, 0, 1);
		glTranslatef(0, -(int)((static_this->field.get_size_x() + 2) / PERSPECTIVE_CONST_X), 0);
		break;
	case GLUT_KEY_DOWN:
		glTranslatef(0, (int)((static_this->field.get_size_x() + 2) / PERSPECTIVE_CONST_X), 0);
		glRotatef(-static_this->angle_z, 0, 0, 1);
		glRotatef(-5, 1, 0, 0);
		glRotatef(static_this->angle_z, 0, 0, 1);
		glTranslatef(0, -(int)((static_this->field.get_size_x() + 2) / PERSPECTIVE_CONST_X), 0);
		break;
	}
}