#pragma once
#include "LightSource.h"
#include "Material.h"
#include "Cubo.h"

#define CENTER_X 10.0
#define CENTER_Y 10.0

class Lamp :
	public LightSource
{
private:
	float _height = 1.5;
	Material *_poste, *_lampada, *_pavio;
	int _nlamps;
public:
	Lamp(GLenum number, Vector4 position, Vector4 ambientLight, Vector4 diffuseLight, Vector4 specularLight);
	virtual ~Lamp();
	virtual void draw();
	float getHeight();
};

