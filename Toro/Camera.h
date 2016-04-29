#pragma once
#include <vector>
#include "Entity.h"
#include "Car.h"
using namespace std;

class Camera :
	public Entity
{
public:
	Camera(double near, double far);
	virtual ~Camera();

protected:
	double _near;
	double _far;
	Vector3 _up;
	Vector3 _center;
	Vector3 _at;


public:
	virtual void update(Car* car) = 0;
	virtual void computeProjectionMatrix() = 0;
	virtual void computeVisualizationMatrix() = 0;
};

