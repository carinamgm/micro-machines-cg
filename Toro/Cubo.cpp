#include "Cubo.h"



Cubo::Cubo(float tam) : _tam(tam)
{
}


Cubo::~Cubo()
{
}

void Cubo::draw() {
	glBegin(GL_QUADS);

	//Frente (y = 1)
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(_tam, _tam, -_tam);
	glVertex3f(-_tam, _tam, -_tam);
	glVertex3f(-_tam, _tam, _tam);
	glVertex3f(_tam, _tam, _tam);

	//Atrás (y=-1)
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(_tam, -_tam, _tam);
	glVertex3f(-_tam, -_tam, _tam);
	glVertex3f(-_tam, -_tam, -_tam);
	glVertex3f(_tam, -_tam, -_tam);

	//Cima z=1
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(_tam, _tam, _tam);
	glVertex3f(-_tam, _tam, _tam);
	glVertex3f(-_tam, -_tam, _tam);
	glVertex3f(_tam, -_tam, _tam);

	//Baixo z=-1
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(_tam, -_tam, -_tam);
	glVertex3f(-_tam, -_tam, -_tam);
	glVertex3f(-_tam, _tam, -_tam);
	glVertex3f(_tam, _tam, -_tam);

	//Lado Esquerdo
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-_tam, _tam, _tam);
	glVertex3f(-_tam, _tam, -_tam);
	glVertex3f(-_tam, -_tam, -_tam);
	glVertex3f(-_tam, -_tam, _tam);

	//Lado direito
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(_tam, _tam, -_tam);
	glVertex3f(_tam, _tam, _tam);
	glVertex3f(_tam, -_tam, _tam);
	glVertex3f(_tam, -_tam, -_tam);
	glEnd();
}
