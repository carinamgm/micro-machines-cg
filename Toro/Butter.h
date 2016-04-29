#pragma once
#include "Obstacle.h"
#include <stdlib.h>
#include "GL\glut.h"
#include "Material.h"
#include "Cubo.h"

#define BUTTER_SIZE 0.8

class Butter :
	public Obstacle
{
private:
	Material *_body;
public:
	Butter(double x, double y, double z);
	virtual ~Butter();
	virtual void draw();
	virtual double getObjSize();
	virtual bool collision(DynamicObject *d);
};

