#include "Lamp.h"
#include <iostream>
#include <Windows.h>

#define PI 3.1415926535897
#define RADIUS_FORA 9.8
#define RADIUS_DENTRO 5
#define ZPLANE -0.5

using namespace std;

Lamp::Lamp(GLenum number, Vector4 position, Vector4 ambientLight, Vector4 diffuseLight, Vector4 specularLight): 
	LightSource(number, position, ambientLight, diffuseLight, specularLight)
{
	GLfloat amb[] = { 0.22f,0.37f,0.7f,1.0f };
	GLfloat diff[] = { 1.0f,0.9f,0.8f,1.0f };
	GLfloat spec[] = { 0.4f,0.2f,0.3f,1.0f };
	GLfloat shine = 44.0f;
	_poste = new Material(amb, diff, spec, shine);

	GLfloat ambL[] = { 0.22f,0.37f,0.7f,1.0f };
	GLfloat diffL[] = { 0.55f,0.45f,0.7f,1.0f };
	GLfloat specL[] = { 0.4f,0.2f,0.3f,1.0f };
	GLfloat shineL = 44.0f;
	_lampada = new Material(ambL, diffL, specL, shineL);

	GLfloat ambP[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat diffP[] = { 0.02f,0.02f,0.24f,1.0f };
	GLfloat specP[] = { 0.76f,0.48f,0.3f,1.0f };
	GLfloat shineP = 40.0f;
	_pavio = new Material(ambP, diffP, specP, shineP);

	GLfloat _emission[4] = { 0.0,1.0,0.0,1.0 };
	glLightf(GL_LIGHT0 + number, GL_CONSTANT_ATTENUATION, 0.05);
	glLightf(GL_LIGHT0 + number, GL_LINEAR_ATTENUATION, 0.35);
	glLightf(GL_LIGHT0 + number, GL_QUADRATIC_ATTENUATION, 0.05);
	glLightfv(GL_LIGHT0 + number, GL_EMISSION, _emission);
	

}


Lamp::~Lamp()
{
	delete _lampada;
	delete _poste;
}

float Lamp::getHeight() {
	return _height;
}


void Lamp::draw()
{	
	GLfloat positionTranslated[4] = { _position[0] + CENTER_X,_position[1] + CENTER_Y ,_position[2] + _height + 0.2,_position[3] };
	glLightfv(GL_LIGHT0 + _num, GL_POSITION, positionTranslated);
	
	glPushMatrix();
	
	glTranslatef(10, 10, -1.0);

	glColor3f(0.22f, 0.37f, 0.7f);
	glTranslatef(_position[0], _position[1], 0.0);
	_poste->applyMaterial();
	gluCylinder(gluNewQuadric(), 0.3, 0.32, _height, 20, 20);
	
	glPushMatrix();
	glTranslatef(0, 0, 1.5);
	glColor3f(0.29f, 0.45f, 0.80f);
	_lampada->applyMaterial();
	gluCylinder(gluNewQuadric(), 0.32, 0.0, 0.2, 20, 20);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, 1.70);
	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_NORMALIZE);
	glScalef(0.1, 0.1, 1.0);
	_pavio->applyMaterial();
	Cubo cube = Cubo(0.1);
	cube.draw();
	glDisable(GL_NORMALIZE);
	glPopMatrix();

	glPopMatrix();

	
}
