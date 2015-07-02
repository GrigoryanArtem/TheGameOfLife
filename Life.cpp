#include <cstdlib>
#include <glut.h>

#include "Life.h"

Life *Life::static_this;

void Life::start_game(int argc, char** argv){
	this->field.generate();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("<= Life by.GrigoryanArtem =>");

	this->init_gl();
	glutDisplayFunc(&Life::draw_game);

	glutMainLoop();
}

void Life::init_gl(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, this->field.get_size_y() + 1, 0, this->field.get_size_x() + 1, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Life::draw_game(){
	glClear(GL_COLOR_BUFFER_BIT);

	static_this->field.draw();

	glutSwapBuffers();
}