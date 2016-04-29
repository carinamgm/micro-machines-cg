#pragma once
#include "DynamicObject.h"
#include <vector>
#include "GLError.h"
#include "Vector3.h"
#include "Material.h"
#include "Spotlight.h"
#define FAST_FURIOUS 0.1
#define PI 3.1415926
#define MAX_KEYS 256
#define ANGLE_INCREASE 5
#define STARTING_X 9
#define STARTING_Y -2.5
#define LIVES 5

class Car :
	public DynamicObject
{
private:
	Spotlight* _farol[2];
	double _speedLength = 0.0;
	double _angle = 0.0;
	bool _isToStop = false;
	bool _keyState[MAX_KEYS];
	bool _crashed = false;
	bool _foward = false;
	Material *_carrocaria, *_vidros, *_topo, *_rodas, *_farois;
	Vector3* _normaisJanela[4];
	bool _normaisJanelasCalc = false;
	int _lives = LIVES;
public:
	Car(bool car);
	virtual ~Car();
	void draw();
	void drawCarrocaria(float x, float y, float z);
	void drawTejadilho(float x, float y, float z);
	void drawTopo(float x, float y, float z);
	void addAngle(double angle);
	virtual void update(double delta_t);
	void accelerate();
	void deaccelerate();
	void startStopping();
	void choseBehaviour();
	void setKeyState(int key, bool pressed);
	double getAngle();
	double getSpeedLength();
	virtual double getObjSize();
	void stopCar();
	void reset();
	void drawWheel(GLfloat center_x, GLfloat center_y, GLfloat center_z, GLfloat size, GLfloat height);
	Vector3* calcNormal(Vector3 v1, Vector3 v2);
	int getLives();
	void faroisEnable();
	void faroisDisable();
	void instanceCar();
};

