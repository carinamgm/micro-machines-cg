#include "ThirdPerson.h"
#include "GL\glut.h"
#include <iostream>
#include <math.h>

using namespace std;

#define DIST_CAM_CAR 3.0
#define ZPLANE -1.0

ThirdPerson::ThirdPerson(double fovy, double aspect, double zNear, double zFar) :
	_fovy(fovy), _aspect(aspect), Camera(zNear, zFar)
{
}


ThirdPerson::~ThirdPerson()
{
}

void ThirdPerson::update(Car* car)
{
	// Sistema de coordenadas do carro está em -y onde é x e x onde é y
	Vector3* pos = car->getPosition();
	Vector3* speed = car->getSpeed();

	double angle = car->getAngle() - 90;

	_up.set(0.0, 0.0, 1.0);

	double eyeX = -pos->getY() + cos(angle*PI / 180)*(DIST_CAM_CAR);
	double eyeY = pos->getX() + sin(angle*PI / 180)*(DIST_CAM_CAR);
	// O quão para cima vemos a câmara //
	double eyeZ = 2.0;

	// troquei a ordem do y com o x pra ver o carro bem
	_at.set(eyeX, eyeY, eyeZ);

	_center.set(-pos->getY(), pos->getX(), ZPLANE);

}


void ThirdPerson::computeProjectionMatrix()
{

	gluPerspective(90, _aspect, _near, _far);
}


void ThirdPerson::computeVisualizationMatrix()
{

	gluLookAt(_at.getX(), _at.getY(), _at.getZ(), _center.getX(), _center.getY(), _center.getZ(), _up.getX(), _up.getY(), _up.getZ());

}