#pragma once
#include "DynamicObject.h"
class Obstacle :
	public DynamicObject
{
public:
	Obstacle();
	virtual ~Obstacle();
	double virtual getObjSize() = 0;
};

