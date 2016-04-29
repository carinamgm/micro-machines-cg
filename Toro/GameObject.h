#pragma once
#include "Entity.h"
class GameObject :
	public Entity
{
public:
	GameObject();
	void virtual draw() = 0;
	void virtual update(double delta_t) = 0;
	virtual ~GameObject();

};

