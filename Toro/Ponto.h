#pragma once
#include "Vector3.h"
#include "DynamicObject.h"
#include <iostream>

#define DECREASE_FAC 0.006

class Ponto :
	public DynamicObject
{
private:
	double _size;
public:
	Ponto(double x, double y, double z, double size);
	virtual ~Ponto();
	bool collision(DynamicObject* d);
	double getObjSize();
	void draw();
};

