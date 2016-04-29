#include "DynamicObject.h"
#include <iostream>
#include "Car.h"
#include <cmath>
#include <Windows.h>

#define DECREASE_FAC 0.006
#define LIM 20.0

using namespace std;

DynamicObject::DynamicObject()
{
	_speed = new Vector3();
}


DynamicObject::~DynamicObject()
{
	delete _speed;
}


void DynamicObject::update(double delta_t)
{
	Vector3 *p = Entity::getPosition();
	Vector3 *s = getSpeed();
	
	/* VELOCIDADE EM X*/
	if (_speed->getX() > 0) {
		if (_speed->getX() - DECREASE_FAC <= 0)
			_speed->set(0.0, _speed->getY(), _speed->getZ());
		else
			_speed->set(_speed->getX() - DECREASE_FAC, _speed->getY(), _speed->getZ());
	}
	else {
		if (_speed->getX() + DECREASE_FAC >= 0)
			_speed->set(0.0, _speed->getY(), _speed->getZ());
		else
			_speed->set(_speed->getX() + DECREASE_FAC, _speed->getY(), _speed->getZ());
	}

	/* VELOCIDADE EM Y*/
	if (_speed->getY() > 0) {
		if (_speed->getY() - DECREASE_FAC <= 0)
			_speed->set(_speed->getX(), 0.0, _speed->getZ());
		else
			_speed->set(_speed->getX(), _speed->getY() - DECREASE_FAC, _speed->getZ());
	}
	else {
		if (_speed->getY() + DECREASE_FAC >= 0)
			_speed->set(_speed->getX(), 0.0, _speed->getZ());
		else
			_speed->set(_speed->getX(), _speed->getY() + DECREASE_FAC, _speed->getZ());
	}
	
	double xpos = p->getX() + _speed->getX();
	double ypos = p->getY() + _speed->getY();
	double zpos = p->getZ() + _speed->getZ();

	if (xpos <= 20.0 - getObjSize() && xpos >= 0.0 + getObjSize() && ypos <= 20.0 - getObjSize() && ypos >= 0.0 + getObjSize()) {
		Entity::setPosition(p->getX() + _speed->getX(), p->getY() + _speed->getY(), p->getZ() + _speed->getZ());
	}

	
}


void DynamicObject::setSpeed(const Vector3 & speed)
{
	*_speed = speed;
}


void DynamicObject::setSpeed(double x, double y, double z)
{
	_speed->set(x, y, z);
}


Vector3* DynamicObject::getSpeed()
{
	return _speed;
}

bool DynamicObject::collision(DynamicObject* d) {
	double selfSize = getObjSize();
	double carSize = d->getObjSize();
	Vector3* posObj = d->getPosition();
	Vector3* selfPos = getPosition();

	double distancia = pow(selfPos->getX() - (-posObj->getY()), 2) + pow(selfPos->getY() - posObj->getX(), 2);
	
	/* Para poder fazer as contas de ajuste */
	double distChoque = carSize + selfSize;
	double dist2 = sqrt(distancia);


	if (dist2 <= distChoque) {
		if (typeid(*d) == typeid(Car)) {
			Car *c = dynamic_cast<Car*>(d);
			double deltaRaio = distChoque - dist2;
			if (c->getSpeedLength() >= 0) {
				posObj->set(posObj->getX() - deltaRaio * cos(c->getAngle() * 3.1415 / 180),
					posObj->getY() - deltaRaio * sin(c->getAngle() * 3.1415 / 180), posObj->getZ());
			}
			else {
				posObj->set(posObj->getX() + deltaRaio * cos(c->getAngle() * 3.1415 / 180),
					posObj->getY() + deltaRaio * sin(c->getAngle() * 3.1415 / 180), posObj->getZ());
			}
		}
		return true;
	}
	else
		return false;
}
