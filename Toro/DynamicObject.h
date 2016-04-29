#pragma once
#include "GameObject.h"
class DynamicObject :
	public GameObject
{
public:
	DynamicObject();
	virtual ~DynamicObject();
private:
	Vector3 *_speed;
public:
	virtual void update(double delta_t);
	void setSpeed(const Vector3 & speed);
	void setSpeed(double x, double y, double z);
	Vector3 *getSpeed();
	double virtual getObjSize() = 0;
	virtual bool collision(DynamicObject* d);

};

