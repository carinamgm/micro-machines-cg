#pragma once
#include "GL\glut.h"
class Material
{
private:
	GLfloat _amb[4];
	GLfloat _diff[4];
	GLfloat _spec[4];
	GLfloat _shin;
public:
	Material(GLfloat *amb, GLfloat *dif, GLfloat *spec, GLfloat shi);
	virtual ~Material();
	void applyMaterial();
};

