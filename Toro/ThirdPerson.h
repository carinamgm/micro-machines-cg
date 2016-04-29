#pragma once
#include "Camera.h"
class ThirdPerson :
	public Camera
{
public:
	ThirdPerson(double fovy, double aspect, double zNear, double zFar);
	virtual ~ThirdPerson();
	virtual void update(Car* car);
	virtual void computeProjectionMatrix();
	virtual void computeVisualizationMatrix();
private:
	double _fovy;
	double _aspect;
};

