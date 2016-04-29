#include "Orange.h"
#include <iostream>
#include "GL\glut.h"
#include <windows.h>
#include "Car.h"



using namespace std;



Orange::Orange(double x, double y, double z)
{
	Entity::setPosition(x, y, z + ORANGE_SIZE);

	Vector3* speed = getSpeed();

	double _speedLength = MIN + (double)rand() / RAND_MAX * (MAX - MIN);

	int res = 4;
	int speedAxis;

	while (res == 4){
		
		res = 4;

		speedAxis = 0 + (rand() % (int)(2 - 0 + 1));
		res += speedAxis;

		if (speedAxis == 1) {
			speed->set(_speedLength, 0.0, 0.0);
			_rotationAnglex = 0.0 + (double)rand() / RAND_MAX * (360.0);
		}
		else if (speedAxis == 2) {
			speed->set(0.0, 0.0, 0.0);
		}
		else {
			speed->set(-_speedLength, 0.0, 0.0);
			_rotationAnglex = -360.0 + (double)rand() / RAND_MAX * (0.0 - (-360.0));
			
		}

		speedAxis = 0 + (rand() % (int)(1 - 0 + 1));
		res += speedAxis;

		if (speedAxis == 1) {
			speed->set(speed->getX(), _speedLength, speed->getZ());
			_rotationAngley = -360.0 + (double)rand() / RAND_MAX * (0.0 - (-360.0));
		}
		else if (speedAxis == 2) {
			speed->set(speed->getX(), 0.0, speed->getZ());
		}
		else {
			speed->set(speed->getX(), -_speedLength, speed->getZ());
			_rotationAngley = 0.0 + (double)rand() / RAND_MAX * (360.0);
		}
	}


	GLfloat amb[] = { 0.35f,0.24f,0.01175f,1.0f };
	GLfloat diff[] = { 0.78f,0.45f,0.0f,1.0f };
	GLfloat spec[] = { 0.727811f,0.626959f,0.626959f,1.0f };
	GLfloat shine = 97;
	_body = new Material(amb, diff, spec, shine);

	GLfloat ambL[] = { 0.0215f,0.1745f,0.0215f,1.0f };
	GLfloat diffL[] = { 0.07568f,0.61424f,0.07568f,1.0f };
	GLfloat specL[] = { 0.633f,0.727811f,0.633f,1.0f };
	GLfloat shineL = 76.8f;

	_leaf = new Material(ambL, diffL, specL, shineL);

}


Orange::~Orange()
{
	delete _body;
	delete _leaf;
}

void Orange::draw()
{

	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	
	Vector3* speed = getSpeed();

	glTranslatef(Entity::getPosition()->getX(), Entity::getPosition()->getY(), Entity::getPosition()->getZ());

	if(speed->getX() != 0 && speed->getY() == 0)
		glRotatef(_rotationAnglex, 0.0, 1.0, 0.0);
	
	if(speed->getX() == 0 && speed->getY() != 0)
		glRotatef(_rotationAngley, 1.0, 0.0, 0.0);

	if (speed->getX() != 0 && speed->getY() != 0){
		if (speed->getY() > 0 && speed->getX() > 0)
			glRotatef(-_rotationAnglex, 1.0, -1.0, 0.0);
		else if (speed->getY() > 0 && speed->getX() < 0) 
			glRotatef(-_rotationAnglex, -1.0, -1.0, 0.0);
		else if (speed->getY() < 0 && speed->getX() > 0)
			glRotatef(_rotationAnglex, 1.0, 1.0, 0.0);
		else if (speed->getY() < 0 && speed->getX() < 0) 
			glRotatef(_rotationAnglex, -1.0, 1.0, 0.0);
	}

	_body->applyMaterial();

	//Laranja
	glColor3d(1, 0.5, 0);
	glPushMatrix();
	glutSolidSphere(ORANGE_SIZE, 50, 50);
	glPopMatrix();

	_leaf->applyMaterial();

	//Caule
	glEnable(GL_NORMALIZE);
	glColor3d(0.1, 0.6, 0.2);
	glPushMatrix();
	glTranslated(0.0, 0.0, ORANGE_SIZE);
	glScalef(0.05, 0.05, 0.4);
	Cubo caule = Cubo(1);
	caule.draw();
	glPopMatrix();

	//Folha
	glPushMatrix();
	glTranslated(-0.1,0.0, ORANGE_SIZE+0.2);
	glRotated(-45, 1, 1, 0);
	glScalef(LEAF_SIZE, 0.1, 0.2);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
	glDisable(GL_NORMALIZE);
	
	glTranslatef(-Entity::getPosition()->getX(), -Entity::getPosition()->getY(), -Entity::getPosition()->getZ());

	glPopMatrix();
}

void Orange::update(double delta_t) {
	
	Vector3 *speed = getSpeed();
	Vector3 *pos = getPosition();

	if (_velIncrement < MAX_VEL_INC) {
		_velIncrement += delta_t / (delta_t * 1000);
		_angleIncrement += ANG_INC;
	}

	if (speed->getX() != 0) {
		if (_rotationAnglex < 0.0)
			_rotationAnglex -= _angleIncrement;
		else
			_rotationAnglex += _angleIncrement;
	}

	if (speed->getY() != 0) {
		if (_rotationAngley < 0.0)
			_rotationAngley -= _angleIncrement;
		else
			_rotationAngley += _angleIncrement;
	}

	pos->set(pos->getX() + speed->getX()*_velIncrement, pos->getY() + speed->getY()*_velIncrement, pos->getZ());

}


double Orange::getObjSize() 
{
	return ORANGE_SIZE;
}

bool Orange::collision(DynamicObject* d) {
	bool value = DynamicObject::collision(d);
	if (value) {
		if (typeid(*d) == typeid(Car)) {
			Car *c = dynamic_cast<Car*>(d);
			c->reset();
		}
	}
	return value;

}