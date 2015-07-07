#include <cstdlib>
#include <glut.h>

#include "Life.h"

Life *Life::static_this;

Life::Life(size_t size_x, size_t size_y, size_t max_level) : field(size_x, size_y, max_level){
	static_this = this;
}

void Life::start_game(int argc, char** argv){
	this->field.generate();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("<= Life by.GrigoryanArtem =>");

	this->init_gl();
	glutDisplayFunc(&Life::draw_game);
	glutTimerFunc(50,&Life::timer_game,0);

	glutMainLoop();
}

void Life::init_gl(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(63, (float)1280 / 720, 1, 10000); 
	glTranslatef(-54.0, -30.0, -50.0);
	glRotatef(-45, 1, 0, 0);

	//glOrtho(0, this->field.get_size_y() + 2, 0, this->field.get_size_x() + 2, -100, 100);

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