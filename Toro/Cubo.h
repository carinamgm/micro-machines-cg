#pragma once
#include "GL\glut.h"
class Cubo
{
private:
	float _tam;
public:
	Cubo(float tam);
	virtual ~Cubo();
	void draw();
};

