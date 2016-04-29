#include "Butter.h"
#include <typeinfo>
#include "Car.h"


using namespace std;


Butter::Butter(double x, double y, double z)
{
	Entity::setPosition(x, y, z);

	GLfloat amb[] = { 0.74f,0.71f,0.0f,1.0f };
	GLfloat diff[] = { 0.5f,0.5f,0.4f,1.0f };
	GLfloat spec[] = { 0.7f,0.7f,0.87f,1.0f };
	GLfloat shine = 32.0f;

	_body = new Material(amb, diff, spec, shine);
}


Butter::~Butter()
{
	delete _body;
}


void Butter::draw()
{
	glPushMatrix();
	_body->applyMaterial();
	glColor3d(1, 1, 0);
	glTranslated(Entity::getPosition()->getX(), Entity::getPosition()->getY(), Entity::getPosition()->getZ() + BUTTER_SIZE / 2);
	Cubo manteiga = Cubo(BUTTER_SIZE / 2.0);
	manteiga.draw();
	glPopMatrix();
}

double Butter::getObjSize() {
	return BUTTER_SIZE / 2.0;
}

bool Butter::collision(DynamicObject* d) {
	bool value = DynamicObject::collision(d);
	if (value) {
		if (typeid(*d) == typeid(Car)) {
			Car *c = dynamic_cast<Car*>(d);
			getSpeed()->set(-d->getSpeed()->getY(), d->getSpeed()->getX(), d->getSpeed()->getZ());
			c->stopCar();
		}
	}
	return value;
}
