#include "Ponto.h"
#include "Vector3.h"

Ponto::Ponto(double x, double y, double z, double size) : _size(size)
{	
	getPosition()->set(x, y, z);
}


Ponto::~Ponto()
{
}

void Ponto::draw() {

}

bool Ponto::collision(DynamicObject* d) {
	return DynamicObject::collision(d);
}

double Ponto::getObjSize() {
	return _size;
}
