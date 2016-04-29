#pragma once
#include <vector>
#include "Camera.h"
#include "LightSource.h"
#include "GameObject.h"
#include "Car.h"
#include "Orange.h"
#include "Ponto.h"
#include "Timer.h"
#include "DynamicObject.h"
#include "Roadside.h"

#define NR_BUTTERS 5
#define NR_ORANGES 5
#define NR_OBJECTS NR_BUTTERS + NR_ORANGES + 1
#define NR_TEXTURES 3

using namespace std;

class GameManager
{
private:
	vector<Timer*> _timers;
	Camera* _currentCamera;
	vector<Camera*> _cameras;
	vector<LightSource*> _lightSources;
	vector<DynamicObject*> _dynamicObjects;
	Roadside* _roadSide;
	double _oldTime = 0.0;
	Car* rodolfo;
	GLenum _drawMode = GL_FILL;
	bool _shading = false;
	GLuint *_textures;
	bool _pause = false;
	bool _go = false;
public:
	GameManager(char *path);
	virtual ~GameManager();
	void display();
	void reshape(GLsizei w, GLsizei h);
	void keyPressed(int key, int x, int y);
	void keyPressed(unsigned char key, int x, int y);
	void keyReleased(int key, int x, int y);
	void onTimer(int value);
	void idle();
	void update();
	void init();
	double randomDouble(double max, double min);
	void createEnvironment();
	void createCameras();
	void respawnOrange();
	void checkCollisions();
	void manageOranges(double delta_t);
	void createLights();
	void showMessage(int message);
	void gameOver();
	void restart();
	void iterateLives();
};

