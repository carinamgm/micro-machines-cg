#pragma once
#include "LightSource.h"
class Spotlight :
	public LightSource
{
public:
	Spotlight(GLenum number, Vector4 position, Vector4 ambientLight, Vector4 DiffuseLight, Vector4 SpecularLight, GLfloat cutoff, GLfloat exponent, Vector3 direction);
	virtual void draw();
	virtual ~Spotlight();
};

