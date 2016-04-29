#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include "GLError.h"
#include "GameManager.h"

#define WINDOW_SIZE_X 600
#define WINDOW_SIZE_Y 600
#define GAME_TITLE "MicroMachines"
#define TIMER_MS 17 //60 FPS

using namespace std;

GameManager *gm;

void reshape(GLsizei w, GLsizei h);
void keyPressed(int key, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void onTimer(int value);
void update();
void display();
void keyReleased(int key, int x, int y);
void Initialize();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |GLUT_DEPTH);
	glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	glutInitWindowPosition(-1, -1);
	glutCreateWindow(GAME_TITLE);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyPressed);
	glutKeyboardFunc(keyPressed);
	glutSpecialUpFunc(keyReleased);
	glutDisplayFunc(display);
	glutTimerFunc(TIMER_MS, onTimer, 1);
	srand(time(NULL));
	Initialize();
	gm = new GameManager(argv[0]);

	glutMainLoop();
	delete gm;
	return 0;
}

void Initialize() {
	gm->init();
}

void reshape(GLsizei w, GLsizei h) {
	gm->reshape(w, h);
}

void keyPressed(int key, int x, int y) {
	gm->keyPressed(key, x, y);
}
void keyPressed(unsigned char key, int x, int y) {
	gm->keyPressed(key, x, y);
}

void onTimer(int value) {
	gm->onTimer(value);
	glutTimerFunc(TIMER_MS, onTimer, 1);
}

void update() {
	gm->update();

}

void display() {
	gm->display();
}

void keyReleased(int key, int x, int y) {
	gm->keyReleased(key, x, y);
}