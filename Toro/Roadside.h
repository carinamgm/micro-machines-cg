#pragma once
#include "StaticObject.h"
#include "stdlib.h"
#include <iostream>
#include "Car.h"
#include "Ponto.h"
#include <stdio.h>
#include <vector>
#include "Material.h"
#include "Cubo.h"
#include "GL\glut.h"

using namespace std;

#define RADIUS_FORA 9.5
#define RADIUS_DENTRO 6
#define _USE_MATH_DEFINES 
#define ZPLANE -1.0
#define DETAIL_LEVEL 0.25	//Largura dos polignos da malha

class Roadside :
	public StaticObject
{
private:
	Material *_mat, *_torusMat;
	vector<Ponto*> _mapCoords;
public:
	Roadside();
	virtual ~Roadside();
	void virtual draw();
	void virtual update(double delta_t);
	vector<Ponto*> getMapCoords();
	virtual void collision(DynamicObject* d);
	void malha();
};

