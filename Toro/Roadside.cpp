#include "Roadside.h"
#include <math.h>
#include <windows.h>

#define OUTER_RADIUS 0.075
#define INNER_RADIUS 0.025

Roadside::Roadside(){
	GLfloat amb[] = { 0.10f,0.10f,0.10f,1.0f };
	GLfloat diff[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat spec[] = { 0.508273f,0.508273f,0.508273f,1.0f };
	GLfloat shine = 51.2f;
	_mat = new Material(amb, diff, spec, shine);

	GLfloat ambG[] = { 0.35f,0.1995f,0.0745f,1.0f };
	GLfloat diffG[] = { 0.74f,0.77f,0.22648f,1.0f };
	GLfloat specG[] = { 0.628281f,0.555802f,0.366065f,1.0f };
	GLfloat shineG = 36;

	_torusMat = new Material(ambG, diffG, specG, shineG);
}

void Roadside::draw() {

	glPushMatrix();
	_mat->applyMaterial();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(0, 0, -1);
	glEnable(GL_TEXTURE_2D);
   /* Cubo plataforma = Cubo(10.0);
	plataforma.draw();*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	malha();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	_torusMat->applyMaterial();
	if (_mapCoords.size() == 0) {
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(10, 10, 0);
		
		for (double i = 0; i < 2 * M_PI - M_PI/12; i += M_PI / 12) {
			glPushMatrix();

			double x = cos(i) * RADIUS_FORA;
			double y = sin(i) * RADIUS_FORA;
			_mapCoords.push_back(new Ponto(x + 10.0, y + 10.0, ZPLANE, OUTER_RADIUS));

			glTranslatef(x, y, ZPLANE);
			glutSolidTorus(INNER_RADIUS, OUTER_RADIUS, 20, 20);

			glPopMatrix();
		}
		/* - M_PI/12 senão desenhava 1 a mais no 0 graus*/
		for (double i = 0; i < 2 * M_PI - M_PI / 12; i += M_PI / 12) {
			glPushMatrix();

			double x = cos(i) * RADIUS_DENTRO;
			double y = sin(i) * RADIUS_DENTRO;
			_mapCoords.push_back(new Ponto(x + 10.0, y + 10.0, ZPLANE, OUTER_RADIUS));

			glTranslatef(x, y, ZPLANE);
			glutSolidTorus(INNER_RADIUS, OUTER_RADIUS, 20, 20);

			glPopMatrix();
		}

		glPopMatrix();

	}
	else {
		glColor3f(1, 1, 0);
		for each (Ponto* p in _mapCoords) {
			Vector3* pos = p->getPosition();
			glPushMatrix();
			glTranslatef(pos->getX(), pos->getY(), pos->getZ());
			glutSolidTorus(INNER_RADIUS, OUTER_RADIUS, 20, 20);
			glPopMatrix();
		}
	}

	//Ponto de Partida
	glPushMatrix();
	glTranslatef(0.68, 9.8, -0.99);
	glScaled(0.35, 0.1, 0.0);
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 4; ++j) {
			if ((i + j) % 2 == 0)
				glColor3f(0.0, 0.0, 0.0);
			else
				glColor3f(1.0, 1.0, 1.0);
			glRecti(i * 1, j * 1, (i + 1) * 1, (j + 1) * 1); 
		}
	}
	glPopMatrix();

	

}

vector<Ponto*> Roadside::getMapCoords() {
	return _mapCoords;
}

void Roadside::update(double delta_t) {

}

Roadside::~Roadside(){
	for each (Ponto* p in _mapCoords) {
		delete p;
	}
	delete _mat;
	delete _torusMat;
}

void Roadside::collision(DynamicObject* d) {
	bool result = false;
	for each (Ponto *p in _mapCoords) {
		result = p->collision(d);
		if (result) {
			Car *c = dynamic_cast<Car*>(d);
			p->getSpeed()->set(-d->getSpeed()->getY(), d->getSpeed()->getX(), d->getSpeed()->getZ());
			c->stopCar();
		}
	}
}

void Roadside::malha() {
	float sideSize = DETAIL_LEVEL;
	int k = 0;
	for (int count = 0; count < 2; count++) {
		for (float i = 0; i < 20; i += sideSize) {
			for (float j = 0; j < 20; j += sideSize) {
				glBegin(GL_QUADS);
				if (count == 0)
					glNormal3f(0, 0, 1);
				else
					glNormal3f(0, 0, -1);
				
				glTexCoord2f(0, 0);
				glVertex3f(i, j, k);
				glTexCoord2f(1, 0);
				glVertex3f(i + sideSize, j, k);
				glTexCoord2f(1, 1);
				glVertex3f(i + sideSize, j + sideSize, k);
				glTexCoord2f(0, 1);
				glVertex3f(i, j + sideSize, k);
				glEnd();

			}
		}
		//Otimizacao: As outras faces da mesa nao sao tao visiveis, vamos diminuir o promenor da malha
		sideSize = DETAIL_LEVEL * 4;
		k = -20;
	}
	k = 0;
	for (int count = 0; count < 2; count++) {
		for (float i = 0; i < 20; i += sideSize) {
			for (float j = 0; j < 20; j += sideSize) {
				glBegin(GL_QUADS);
				if (count == 0)
					glNormal3f(1, 0, 0);
				else
					glNormal3f(-1, 0, 0);
				
				glTexCoord2f(0, 0);
				glVertex3f(k, j, -i);
				glTexCoord2f(1, 0);
				glVertex3f(k, j, -(i + sideSize));
				glTexCoord2f(1, 1);
				glVertex3f(k, j + sideSize, -(i + sideSize));
				glTexCoord2f(0, 1);
				glVertex3f(k, j + sideSize, -i);
				glEnd();

			}
		}
		k = 20;
	}
	k = 0;
	for (int count = 0; count < 2; count++) {
		for (float i = 0; i < 20; i += sideSize) {
			for (float j = 0; j < 20; j += sideSize) {
				glBegin(GL_QUADS);
				if (count == 0)
					glNormal3f(0, 1, 0);
				else
					glNormal3f(0, -1, 0);
				glTexCoord2f(0, 0);
				glVertex3f(j, k, -i);
				glTexCoord2f(1, 0);
				glVertex3f(j, k, -(i + sideSize));
				glTexCoord2f(1, 1);
				glVertex3f(j + sideSize, k, -(i + sideSize));
				glTexCoord2f(0, 1);
				glVertex3f(j + sideSize,k , -i);
				glEnd();

			}
		}
		k = 20;
	}
}