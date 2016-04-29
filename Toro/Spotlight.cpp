#include "Spotlight.h"



Spotlight::Spotlight(GLenum number, Vector4 position, Vector4 ambientLight, Vector4 DiffuseLight, Vector4 SpecularLight, GLfloat cutoff, GLfloat exponent, Vector3 direction):
	LightSource(number, position, ambientLight, DiffuseLight, SpecularLight)
{
	setCutOff(cutoff);
	setExponent(exponent);
	setDirection(direction);
	glLightf(GL_LIGHT0 + number, GL_SPOT_CUTOFF, _cut_off);
	glLightf(GL_LIGHT0 + number, GL_SPOT_EXPONENT, _exponent);
	glLightfv(GL_LIGHT0 + number, GL_SPOT_DIRECTION, _direction);

	glLightf(GL_LIGHT0 + number, GL_CONSTANT_ATTENUATION, 0.05);
	glLightf(GL_LIGHT0 + number, GL_LINEAR_ATTENUATION, 0.005);
	glLightf(GL_LIGHT0 + number, GL_QUADRATIC_ATTENUATION, 0.005);
}

void Spotlight::draw() {
	LightSource::draw();
	glLightfv(GL_LIGHT0 + _num, GL_SPOT_DIRECTION, _direction);
}

Spotlight::~Spotlight()
{
}
