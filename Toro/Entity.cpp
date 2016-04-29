#include "Entity.h"
#include <iostream>
using namespace std;

Entity::Entity()
{
	_position = new Vector3();
}


Entity::~Entity()
{
	delete _position;
}

Vector3* Entity::getPosition() {
	return _position;
}

Vector3* Entity::setPosition(double x, double y, double z) {
	_position->set(x, y, z);
	return _position;
}

Vector3* Entity::setPosition(const Vector3 &p) {
	_position->set(p.getX(), p.getY(), p.getZ());
	return _position;
}
