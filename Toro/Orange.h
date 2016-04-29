#pragma once
#include "Obstacle.h"
#include <stdlib.h> 
#include "DynamicObject.h"
#include "GL\glut.h"
#include "Material.h"
#include "Cubo.h"

#define ORANGE_SIZE 0.75
#define NR_ORANGE 3
#define LEAF_SIZE 0.05
#define ANGLE_INC 1.0
#define MAX_VEL_INC 0.5
#define ANG_INC 0.05


#define MIN 0.25
#define MAX 0.5

class Orange :
	public Obstacle
{
private:
	double _rotationAnglex = 0.0;
	double _rotationAngley = 0.0;
	double _speedLength = 0.0;
	double _velIncrement = 0.0;
	double _angleIncrement = 0.0;
	bool _projMatrix = false;
	Material *_body, *_leaf;
public:
	Orange(double x, double y, double z);
	virtual ~Orange();
	virtual void draw();
	virtual void update(double delta_t);
	virtual double getObjSize();
	virtual bool collision(DynamicObject *d);

};

