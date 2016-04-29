#include <iostream>
#include "Car.h"
#include <cmath>
#include "GL/glut.h"
#include <Windows.h>

using namespace std;

#define ZPLANE -0.85
#define LIM 20.0

Car::Car(bool car)
{
	if (car) {
		Vector3 *pos = getPosition();
		pos->set(STARTING_X, STARTING_Y, ZPLANE);

		GLfloat amb_carrocaria[4] = { 1.0f,0.15f,0.15f,1.0f };
		GLfloat diff_carrocaria[4] = { 0.5f,0.0f,0.0f,1.0f };
		GLfloat spec_carrocaria[4] = { 0.7f,0.6f,0.6f,1.0f };
		GLfloat shine_carrocaria = 32.0f;
		_carrocaria = new Material(amb_carrocaria, diff_carrocaria, spec_carrocaria, shine_carrocaria);

		GLfloat amb_tejadilho[] = { 0.46f,1.0f,1.0f,1.0f };
		GLfloat diff_tejadilho[] = { 0.71f,0.74151f,0.84f,1.0f };
		GLfloat spec_tejadilho[] = { 0.297254f,0.30829f,0.29f,1.0f };
		GLfloat shine_tejadilho = 9.0f;

		_vidros = new Material(amb_tejadilho, diff_tejadilho, spec_tejadilho, shine_tejadilho);

		GLfloat amb_topo[4] = { 1.0f,0.15f,0.15f,1.0f };
		GLfloat diff_topo[4] = { 0.5f,0.0f,0.0f,1.0f };
		GLfloat spec_topo[4] = { 0.7f,0.6f,0.6f,1.0f };
		GLfloat shine_topo = 32.0f;

		_topo = new Material(amb_topo, diff_topo, spec_topo, shine_topo);

		GLfloat ambR[] = { 0.5f,0.5f,0.5f,1.0f };
		GLfloat diffR[] = { 0.01f,0.01f,0.01f,1.0f };
		GLfloat specR[] = { 0.4f,0.4f,0.4f,1.0f };
		GLfloat shineR = 10;

		_rodas = new Material(ambR, diffR, specR, shineR);

		GLfloat farolAmb[] = { 1.0f,1.0f,0.0f,1.0f };
		GLfloat farolDiff[] = { 1.0f,1.0f,0.98f,1.0f };
		GLfloat farolSpec[] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat farolShine = 128.0;

		_farois = new Material(farolAmb, farolDiff, farolSpec, farolShine);

		/* Farol na generalidade */
		Vector4 spotPosition = Vector4(0, 0, 0, 1.0);
		Vector4 spotAmbient = Vector4(0.4, 0.4, 0.4, 1.0);
		Vector4 spotDiffuse = Vector4(0.6, 0.6, 0.6, 1.0);
		Vector4 spotSpecular = Vector4(1.0, 1.0, 1.0, 1.0);

		/* Farol direita */
		Vector3 spotDirection = Vector3(-1.0, 0.2, 0.0);
		_farol[0] = new Spotlight(6, spotPosition, spotAmbient, spotDiffuse, spotSpecular, 85, 20, spotDirection);

		/* Farol esquerda */
		spotDirection = Vector3(-1.0, -0.2, 0.0);
		_farol[1] = new Spotlight(7, spotPosition, spotAmbient, spotDiffuse, spotSpecular, 85, 20, spotDirection);
	}

}


Car::~Car()
{
	for (int i = 0; i < 2; i++) {
		delete _farol[i];
	}
	delete _carrocaria;
	delete _rodas;
	delete _farois;
	delete _topo;
	delete _vidros;
}

void Car::draw() {
	Vector3 *pos = getPosition();

	if (!(pos->getX() <= LIM - getObjSize() && pos->getX() >= 0.0 + getObjSize() && (-pos->getY()) <= LIM - getObjSize() && (-pos->getY()) >= 0.0 + getObjSize())) {
		reset();
	}

	glPushMatrix();
	glRotated(-90, 0, 0, 1);
	glTranslated(-pos->getX(), -pos->getY(), ZPLANE);
	glRotated(_angle, 0, 0, 1);

	/* Farol direita */
	glPushMatrix();
	glColor3d(1, 1, 1);
	glTranslatef(-0.55, 0.15, 0.0);
	_farois->applyMaterial();
	glutSolidSphere(0.10, 50, 50);
	_farol[0]->draw();
	glPopMatrix();

	/* Farol esquerda */
	glPushMatrix();
	glColor3d(1, 1, 1);
	glTranslatef(-0.55, -0.15, 0.0);
	_farois->applyMaterial();
	glutSolidSphere(0.10, 50, 50);
	_farol[1]->draw();
	glPopMatrix();


	//Carroçaria
	glPushMatrix();
	glColor3f(1.0, 0.15, 0.15);
	_carrocaria->applyMaterial();
	glTranslatef(0.0, 0.0, 0.045);
	drawCarrocaria(0.525, 0.3, 0.135);
	glPopMatrix();

	//Vidros
	glPushMatrix();
	glColor3f(0.46f, 1.0f, 1.0f);
	glTranslatef(0.1125, 0.0, 0.18);
	_vidros->applyMaterial();
	drawTejadilho(0.36, 0.3, 0.15);
	glPopMatrix();

	//Topo
	glPushMatrix();
	glColor3f(1.0, 0.15, 0.15);
	glTranslatef(0.1125, 0.0, 0.345);
	_topo->applyMaterial();
	drawTopo(0.19, 0.3, 0.03);
	glPopMatrix();

	//Rodas
	glPushMatrix();
	glColor3f(0, 0, 0);
	_rodas->applyMaterial();
	drawWheel(0.35, 0.3, 0, 0.10, 0.07);
	drawWheel(0.35, -0.37, 0, 0.10, 0.07);
	drawWheel(-0.35, 0.3, 0, 0.10, 0.07);
	drawWheel(-0.35, -0.37, 0, 0.10, 0.07);
	glPopMatrix();

	glPopMatrix();

}

void Car::drawCarrocaria(float x, float y, float z) {
	glBegin(GL_QUADS);


	//Lateral direito
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);

	//Lateral esq
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);

	//Cima
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);

	//Baixo
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(x, -y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);

	//Frente
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(-x, y, z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);

	//Tras
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);
	glEnd();
	
}

void Car::drawTejadilho(float x, float y, float z) {

	//Janelas de lado
	
	if (_normaisJanelasCalc == false) {
		_normaisJanela[0] = calcNormal(Vector3(0, x / 2 , z), Vector3(0, 2 * x, 0));
		_normaisJanela[1] = calcNormal(Vector3(0,x/2,z), Vector3(0,2*x,0));
		_normaisJanela[2] = calcNormal(Vector3(0, x / 2 ,z), Vector3(-2*y,0,0));
		_normaisJanela[3] = calcNormal(Vector3(0,-x/2,z), Vector3(-2*y,0,0));
		_normaisJanelasCalc = true;
	}

	// Janela esq
	glBegin(GL_POLYGON);
	glNormal3f(_normaisJanela[0]->getX(), _normaisJanela[0]->getY(), _normaisJanela[0]->getZ());
	glVertex3f(-x, -y, 0);
	glVertex3f(-x/2, -y, z);
	glVertex3f(x/2, -y, z);
	glVertex3f(x, -y, 0.0);
	glEnd();

	//Janela Direita
	glBegin(GL_POLYGON);
	glNormal3f(_normaisJanela[1]->getX(), _normaisJanela[1]->getY(), _normaisJanela[1]->getZ());
	glVertex3f(-x, y, 0);
	glVertex3f(-x/2, y, z);
	glVertex3f(x/2, y, z);
	glVertex3f(x, y, 0.0);
	glEnd();
	
	//Janela Frente
	glBegin(GL_QUADS);
	glNormal3f(_normaisJanela[2]->getX(), _normaisJanela[2]->getY(), _normaisJanela[2]->getZ());
	glVertex3f(-x, -y, 0);
	glVertex3f(-x/2, -y, z);
	glVertex3f(-x/2, y, z);
	glVertex3f(-x, y, 0);
	glEnd();

	//Janela Atrás
	glBegin(GL_QUADS);
	glNormal3f(_normaisJanela[3]->getX(), _normaisJanela[3]->getY(), _normaisJanela[3]->getZ());
	glVertex3f(x, -y, 0);
	glVertex3f(x/2, -y, z);
	glVertex3f(x/2, y, z);
	glVertex3f(x, y, 0);
	glEnd();

}

void Car::drawTopo(float x, float y, float z) {
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3d(x, y, 0);
	glVertex3d(x, -y, 0);
	glVertex3d(-x, -y, 0);
	glVertex3d(-x, y, 0);
	glEnd();
}

void Car::drawWheel(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat height) {

	float firstHex[6][3];
	float secHex[6][3];
	glNormal3f(0, -1, 0);
	glBegin(GL_POLYGON);

	for (int i = 0; i < 6; i++)
	{
		float angle = 2 * PI / 6 * (i + 0.5);
		float xVertice = x + size * cos(angle);
		float zVertice = z + size * sin(angle);
		firstHex[i][0] = xVertice;
		firstHex[i][1] = y;
		firstHex[i][2] = zVertice;
		glVertex3f(xVertice, y, zVertice);
	}

	glEnd();
	glNormal3f(0, 1, 0);
	glBegin(GL_POLYGON);

	for (int i = 0; i < 6; i++)
	{
		float angle = 2 * PI / 6 * (i + 0.5);
		float xVertice = x + size * cos(angle);
		float zVertice = z + size * sin(angle);
		secHex[i][0] = xVertice;
		secHex[i][1] = y + height;
		secHex[i][2] = zVertice;
		glVertex3f(xVertice, y + height, zVertice);
	}

	glEnd();

	

	glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);

	for (int i = 0; i < 5; i++)
	{
		glVertex3f(firstHex[i][0], firstHex[i][1], firstHex[i][2]); // top left
		glVertex3f(secHex[i][0], secHex[i][1], secHex[i][2]); // bottom left
		glVertex3f(secHex[i + 1][0], secHex[i + 1][1], secHex[i + 1][2]); // top right
		glVertex3f(firstHex[i + 1][0], firstHex[i + 1][1], firstHex[i + 1][2]); // bottom right
	}

	// Meter o bocado final. Ligar o fim com o inicio
	glVertex3f(firstHex[5][0], firstHex[5][1], firstHex[5][2]); // top left
	glVertex3f(secHex[5][0], secHex[5][1], secHex[5][2]); // bottom left
	glVertex3f(secHex[0][0], secHex[0][1], secHex[0][2]); // top right
	glVertex3f(firstHex[0][0], firstHex[0][1], firstHex[0][2]); // bottom right

	glEnd();
	glDisable(GL_NORMALIZE);
}


void Car::update(double delta_t) {
	

	Vector3 *speed = getSpeed();
	Vector3 *pos = getPosition();

	choseBehaviour();

	if (_isToStop) {
		if (_speedLength > 0) {
			_speedLength -= 0.005;
			if (_speedLength <= 0) {
				_speedLength = 0;
				_isToStop = false;
			}
		}
		else if (_speedLength < 0) {
			_speedLength += 0.005;
			if (_speedLength >= 0) {
				_speedLength = 0;
				_isToStop = false;
			}
		}
	}


	speed->set(_speedLength * cos(_angle * PI / 180), _speedLength * sin(_angle * PI / 180), speed->getZ());
	pos->set(pos->getX() + speed->getX(), pos->getY() + speed->getY(), pos->getZ() + speed->getZ());
		
}
double Car::getSpeedLength() {
	return _speedLength;
}
void Car::addAngle(double angle) {
	if (_speedLength > 0)
		_angle += angle;
	else if (_speedLength < 0)
		_angle -= angle;
}

void Car::accelerate() {
	if (FAST_FURIOUS > _speedLength)
		_speedLength += 0.025;
}

void Car::deaccelerate() {
	if (-FAST_FURIOUS < _speedLength)
		_speedLength -= 0.025;
}

void Car::startStopping() {
	_isToStop = true;
}

void Car::setKeyState(int key, bool pressed) {
	_keyState[key] = pressed;
}

void Car::choseBehaviour() {
	if (!_crashed) {
		if (_keyState[GLUT_KEY_UP])
			accelerate();
		else
			startStopping();

		if (_keyState[GLUT_KEY_DOWN])
			deaccelerate();
		else
			startStopping();
	}
	else {
		if (_foward) {
			if (_keyState[GLUT_KEY_DOWN]) {
				deaccelerate();
				_crashed = false;
			}		
	
			if (!_keyState[GLUT_KEY_UP]) {
				_crashed = false;
				_foward = false;
			}
		}
		else {
			if (_keyState[GLUT_KEY_UP]){
				accelerate();
				_crashed = false;
			}

			if (!_keyState[GLUT_KEY_DOWN]) {
				_crashed = false;
				_foward = true;
			}
		}
	}

	if (_keyState[GLUT_KEY_RIGHT])
		addAngle(-ANGLE_INCREASE);

	if (_keyState[GLUT_KEY_LEFT])
		addAngle(ANGLE_INCREASE);
		
}

double Car::getAngle() {
	return _angle;
}

double Car::getObjSize() {
	double radiusy = 0.525;
	double radiusx = 0.3;
	double radius = sqrt(pow(radiusx, 2) + pow(radiusy, 2));
	return radius/2.0;
}

void Car::stopCar() {
	_crashed = true;
	/* Se a speedLength >= 0 quer dizer que estavamos a ir para cima */
	if (_speedLength > 0.0)
		_foward = true;
	else if (_speedLength < 0.0)
		_foward = false;

	_speedLength = 0.0;
	getSpeed()->set(0.0, 0.0, 0.0);
}

void Car::reset() {
	Vector3 *pos = getPosition();
	/* Caso o carro esteja na partida n deverá perder o jogo, tem imunidade */
	if (_lives > 0 && (pos->getX() != STARTING_X || pos->getY() != STARTING_Y))
		_lives--;
	else {
		_lives = LIVES;
	}
	pos->set(STARTING_X, STARTING_Y, ZPLANE);
	_speedLength = 0;
	Vector3 *speed = getSpeed();
	speed->set(0,0, 0);
	_angle = 0;
	_isToStop = false;
	_foward = false;
	_crashed = false;
}

int Car::getLives() {
	return _lives;
}

void Car::faroisEnable() {
	if (glIsEnabled(GL_LIGHT0 + _farol[0]->getNum()))
		faroisDisable();
	else {
		glEnable(GL_LIGHT0 + _farol[0]->getNum());
		glEnable(GL_LIGHT0 + _farol[1]->getNum());
	}
}

void Car::faroisDisable() {
	glDisable(GL_LIGHT0 + _farol[0]->getNum());
	glDisable(GL_LIGHT0 + _farol[1]->getNum());
}

Vector3* Car::calcNormal(Vector3 v1, Vector3 v2) {
	float x = v1.getY()*v2.getZ() - v2.getY()*v1.getZ();
	float y = v2.getX()*v1.getZ() - v1.getX()*v2.getZ();
	float z = v1.getX()*v2.getY() - v2.getX()*v1.getY();
	float norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	Vector3* normal = new Vector3(x/norm, y/norm, z/norm);
	return normal;
}

void Car::instanceCar() {

	glPushMatrix();
	/* Farol direita */
	glColor3d(1, 1, 1);
	glTranslatef(-0.55, 0.15, 0.0);
	glutSolidSphere(0.10, 50, 50);
	glPopMatrix();

	/* Farol esquerda */
	glPushMatrix();
	glColor3d(1, 1, 1);
	glTranslatef(-0.55, -0.15, 0.0);
	glutSolidSphere(0.10, 50, 50);
	glPopMatrix();

	//Carroçaria
	glPushMatrix();
	glColor3f(1.0, 0.15, 0.15);
	glTranslatef(0.0, 0.0, 0.045);
	drawCarrocaria(0.525, 0.3, 0.135);
	glPopMatrix();

	//Vidros
	glPushMatrix();
	glColor3f(0.46f, 1.0f, 1.0f);
	glTranslatef(0.1125, 0.0, 0.18);
	drawTejadilho(0.36, 0.3, 0.15);
	glPopMatrix();

	//Topo
	glPushMatrix();
	glColor3f(1.0, 0.15, 0.15);
	glTranslatef(0.1125, 0.0, 0.345);
	drawTopo(0.19, 0.3, 0.03);
	glPopMatrix();

	//Rodas
	glPushMatrix();
	glColor3f(0, 0, 0);
	drawWheel(0.35, 0.3, 0, 0.10, 0.07);
	drawWheel(0.35, -0.37, 0, 0.10, 0.07);
	drawWheel(-0.35, 0.3, 0, 0.10, 0.07);
	drawWheel(-0.35, -0.37, 0, 0.10, 0.07);
	glPopMatrix();

	
}