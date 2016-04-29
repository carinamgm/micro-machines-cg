#include "OrthogonalCamera.h"
#include "GL\glut.h"
#include <iostream>



OrthogonalCamera::OrthogonalCamera(double left, double right, double bottom, double top,
	double near, double far) : Camera(near, far), _left(left), _right(right), _bottom(bottom), _top(top)
{
}


OrthogonalCamera::~OrthogonalCamera()
{
}


void OrthogonalCamera::update(Car* car)
{
}


void OrthogonalCamera::computeProjectionMatrix()
{
	glOrtho(_left, _right, _bottom, _top, _near,_far);
}


void OrthogonalCamera::computeVisualizationMatrix()
{
}
