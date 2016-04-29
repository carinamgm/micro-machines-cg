#include "PerspectiveCamera.h"
#include "GL\glut.h"


PerspectiveCamera::PerspectiveCamera(double fovy, double aspect, double zNear, double zFar) :
	_fovy(fovy), _aspect(aspect), Camera(zNear,zFar)
{
}


PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::update(Car* car)
{
}


void PerspectiveCamera::computeProjectionMatrix()
{
	gluPerspective(_fovy, _aspect, _near, _far);
}


void PerspectiveCamera::computeVisualizationMatrix()
{
	gluLookAt(10.0, -3.0, 10, 10, 10, 0, 0, 0, 1);

}
