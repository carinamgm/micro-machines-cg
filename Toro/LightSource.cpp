#include "LightSource.h"
#include "GL/glut.h"
#include <iostream>


LightSource::LightSource(GLenum number, Vector4 position, Vector4 ambientLight, Vector4 diffuseLight, Vector4 specularLight) : _num(number)
{
	setPosition(position);
	setAmbient(ambientLight);
	setDiffuse(diffuseLight);
	setSpecular(specularLight);

	glLightfv(GL_LIGHT0 + number, GL_AMBIENT, _ambient);
	glLightfv(GL_LIGHT0 + number, GL_DIFFUSE, _diffuse);
	glLightfv(GL_LIGHT0 + number, GL_SPECULAR, _specular);

}


LightSource::~LightSource()
{
}


bool LightSource::getState()
{
	return _state;
}

void LightSource::setState(bool state)
{
	_state = state;
}


GLenum LightSource::getNum()
{
	return _num;
}


void LightSource::setPosition(const Vector4& position)
{
	_position[0] = position.getX();
	_position[1] = position.getY();
	_position[2] = position.getZ();
	_position[3] = position.getW();

}


void LightSource::setDirection(const Vector3& direction)
{
	_direction[0] = direction.getX();
	_direction[1] = direction.getY();
	_direction[2] = direction.getZ();
}


void LightSource::setCutOff(double cut_off)
{
	_cut_off = cut_off;
}


void LightSource::setExponent(double exponent)
{
	_exponent = exponent;
}


void LightSource::setAmbient(const Vector4& ambient)
{
	_ambient[0] = ambient.getX();
	_ambient[1] = ambient.getY();
	_ambient[2] = ambient.getZ();
	_ambient[3] = ambient.getW();

}


void LightSource::setDiffuse(const Vector4& diffuse)
{
	_diffuse[0] = diffuse.getX();
	_diffuse[1] = diffuse.getY();
	_diffuse[2] = diffuse.getZ();
	_diffuse[3] = diffuse.getW();
}


void LightSource::setSpecular(const Vector4& specular)
{
	_specular[0] = specular.getX();
	_specular[1] = specular.getY();
	_specular[2] = specular.getZ();
	_specular[3] = specular.getW();
}


void LightSource::draw()
{
	glLightfv(GL_LIGHT0 + _num, GL_POSITION, _position);

}
