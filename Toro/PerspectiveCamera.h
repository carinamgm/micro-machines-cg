#pragma once
#include "Camera.h"
class PerspectiveCamera :
	public Camera
{
public:
	PerspectiveCamera(double fovy, double aspect, double zNear, double zFar);
	virtual ~PerspectiveCamera();
	virtual void update(Car* car);
	virtual void computeProjectionMatrix();
	virtual void computeVisualizationMatrix();
private:
	double _fovy;
	double _aspect;
};

