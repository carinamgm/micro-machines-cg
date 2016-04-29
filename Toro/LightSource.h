
#pragma once
#include <vector>
#include "Vector3.h"
#include "Vector4.h"
#include <GL/glut.h>

using namespace std;

class LightSource
{
private:
	GLfloat _ambient[4];
	GLfloat _diffuse[4];
	GLfloat _specular[4];
	bool _state = false;
	int _nlamps;
protected:
	GLfloat _direction[3];
	GLfloat _position[4];
	GLfloat _cut_off;
	GLfloat _exponent;
	GLenum _num;

public:
	virtual ~LightSource();
	LightSource(GLenum number,Vector4 position, Vector4 ambientLight, Vector4 DiffuseLight, Vector4 SpecularLight);
	bool getState();
	void setState(bool state);
	GLenum getNum();
	void setPosition(const Vector4& position);
	void setDirection(const Vector3& position);
	void setCutOff(double cut_off);
	void setExponent(double exponent);
	void setAmbient(const Vector4& ambient);
	void setDiffuse(const Vector4& diffuse);
	void setSpecular(const Vector4& specular);
	virtual void draw();
};

