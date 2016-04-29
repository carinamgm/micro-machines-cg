#include "GameManager.h"
#include "GL/glut.h"
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include "Roadside.h"
#include "Car.h"
#include "Butter.h"
#include <cmath>
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"
#include "ThirdPerson.h"
#include "Spotlight.h"
#include "Lamp.h"
#include "Texture.h"

#define ZPLANE -1.0
#define FOVY 100.0
#define RESPAWN_TIME 15.0
#define N_LAMPS 5
#define INT_RAND(nmin,nmax) (nmin + (rand() % (int)(nmax - nmin))) 


GameManager::GameManager(char *path)	// Alteracao nao projeto original. Para poder correr sem ter de recompilar
{
	char buffer[MAX_PATH] = {};
	char mesaTex[MAX_PATH] = {};
	char pauseTex[MAX_PATH] = {};
	char goText[MAX_PATH] = {};
	
	/* Serve para dar get dinamicamente das texturas */
	strcpy_s(buffer, path);
	buffer[strlen(path) - 17] = '\0';
	strcpy_s(mesaTex, buffer);
	strcpy_s(pauseTex, buffer);
	strcpy_s(goText, buffer);
	strcat_s(mesaTex, "mesa.bmp");
	strcat_s(pauseTex, "pause512.bmp");
	strcat_s(goText, "go512.bmp");

	char *paths[NR_TEXTURES] = { mesaTex, pauseTex, goText };
	Texture t;
	_textures = t.loadTexture(paths, NR_TEXTURES);
	
	rodolfo = new Car(true);
	createEnvironment();
	createCameras();
	createLights();

	
}


GameManager::~GameManager()
{
	for each (DynamicObject* go in _dynamicObjects) {
		delete go;
	}
	
	for each (LightSource* l in _lightSources) {
		delete l;
	}

	delete _roadSide;

	delete rodolfo;
}


void GameManager::display()
{
	glPolygonMode(GL_FRONT_AND_BACK, _drawMode);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	iterateLives();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (_pause) {
		showMessage(1);
	}
	else if (_go) {
		showMessage(2);
	}
	_currentCamera->computeProjectionMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	_currentCamera->computeVisualizationMatrix();


	for each (LightSource* l in _lightSources) {
		l->draw();
	}

	for each (DynamicObject* go in _dynamicObjects) {
		go->draw();
	}
	
	glBindTexture(GL_TEXTURE_2D, _textures[0]);
	_roadSide->draw();
	
	rodolfo->draw();
	
	//glFlush();
	glutSwapBuffers();//faz glFlush
}


void GameManager::reshape(GLsizei w, GLsizei h)
{
	
	if (w > h)
		glViewport((w - h) / 2, 0, h, h);
	else
		glViewport(0, (h - w) / 2, w, w);

}


void GameManager::keyPressed(int key, int x, int y)
{
	rodolfo->setKeyState(key, true);
}

void GameManager::keyPressed(unsigned char key, int x, int y)
{
	if (!_pause && !_go) {
		if (key == 'a' || key == 'A') {
			if (_drawMode == GL_FILL)
				_drawMode = GL_LINE;
			else
				_drawMode = GL_FILL;
		}
		else if (key == '1' || key == '2' || key == '3') {
			int index = key - '0' - 1;
			_currentCamera = _cameras.at(index);
		}
		else if (key == 'l' || key == 'L') {
			if (glIsEnabled(GL_LIGHTING)) {
				glDisable(GL_LIGHTING);
				for each (LightSource *l in _lightSources)
					glDisable(GL_LIGHT0 + l->getNum());
				rodolfo->faroisDisable();
			}
			else
				glEnable(GL_LIGHTING);
		}
		else if (glIsEnabled(GL_LIGHTING) && (key == 'n' || key == 'N')) {
			if (glIsEnabled(GL_LIGHT0))
				glDisable(GL_LIGHT0);
			else
				glEnable(GL_LIGHT0);
		}
		else if (glIsEnabled(GL_LIGHTING) && (key == 'g' || key == 'G')) {
			if (_shading == false) {
				glShadeModel(GL_FLAT);
				_shading = true;
			}
			else {
				glShadeModel(GL_SMOOTH);
				_shading = false;
			}
		}
		else if (glIsEnabled(GL_LIGHTING) && (key == 'c' || key == 'C')) {
			if (glIsEnabled(GL_LIGHT1)) {
				for each (LightSource* l in _lightSources) {
					if (l == _lightSources[0]) {
						continue;
					}
					glDisable(GL_LIGHT0 + l->getNum());
				}
			}
			else {
				for each (LightSource* l in _lightSources) {
					if (l == _lightSources[0]) {
						continue;
					}
					glEnable(GL_LIGHT0 + l->getNum());
				}
			}
		}
		else if (glIsEnabled(GL_LIGHTING) && (key == 'h' || key == 'H')) {
			rodolfo->faroisEnable();
		}
	}
	if (!_go && (key == 's' || key == 'S')) {
		if (_pause)
			_pause = false;
		else
			_pause = true;
	}
	else if(_go && (key == 'r' || key == 'R')) {
		// Restart do jogo
		restart();

	}

}

void GameManager::keyReleased(int key, int x, int y)
{
	rodolfo->setKeyState(key, false);
}


void GameManager::onTimer(int value)
{
	update();
}


void GameManager::idle()
{
}

void GameManager::init()
{
	glEnable(GL_DEPTH_TEST);

	/* Retirar a luz ambiente default */
	GLint param[4] = {0, 0, 0, 1};
	glLightModeliv(GL_LIGHT_MODEL_AMBIENT, param);

}

void GameManager::update()
{
	if (_pause || _go) {
		glutPostRedisplay();
		return;
	}
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int delta_t = timeSinceStart - _oldTime;
	
	/* Fazer update ao cheerios que foram colididos */
	for each (Ponto* p in _roadSide->getMapCoords()) {
		p->update(delta_t);
	}

	/* Dar despawn e respawn às laranjas */
	manageOranges(delta_t);

	/* Verificar por colisões */
	checkCollisions();

	rodolfo->update(delta_t);

	_currentCamera->update(rodolfo);

	_oldTime = timeSinceStart;

	gameOver();

	glutPostRedisplay();

}

double GameManager::randomDouble(double max, double min) {
	double number = (double)rand() / RAND_MAX;
	return min + number * (max - min);
}

void GameManager::createEnvironment() 
{
	_roadSide = new Roadside();

	for (int i = 0; i < NR_BUTTERS; i++) {
		double x = randomDouble(20.0, 1.0);
		double y = randomDouble(20.0, 1.0);
		_dynamicObjects.push_back(new Butter(x, y, ZPLANE));
	}

	for (int i = 0; i < NR_ORANGES; i++) {
		double x = randomDouble(20.0, 1.0);
		double y = randomDouble(20.0, 1.0);
		_dynamicObjects.push_back(new Orange(x, y, ZPLANE));
	}
}

void GameManager::createCameras() 
{
	_cameras.push_back(new OrthogonalCamera(0.0, 20.0, 0.0, 20.0, -1.0, 30.0));
	_currentCamera = _cameras.at(0);

	double aspect = glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT);
	_cameras.push_back(new PerspectiveCamera(FOVY, 1.0, 0.001, 30.0));

	_cameras.push_back(new ThirdPerson(90, aspect, 0.001, 30.0));
}


void GameManager::manageOranges(double delta_t) 
{
	/* Remover a laranja que caiu e lançar um timer */
	std::vector<DynamicObject*>::iterator it = _dynamicObjects.begin();
	for (; it != _dynamicObjects.end();) {
		DynamicObject* obj = *it;
		obj->update(delta_t);
		Vector3* pos = obj->getPosition();
		if (pos->getX() >= 21.0 || pos->getY() >= 21.0 || pos->getX() < 0.0 || pos->getY() < 0.0) {
			it = _dynamicObjects.erase(it);
			_timers.push_back(new Timer());
			delete obj;
		}
		else {
			++it;
		}
	}

	/* Verificar os timers, se já expiraram de forma a dar respawn de um nova laranja */
	std::vector<Timer*>::iterator iter = _timers.begin();
	for (; iter != _timers.end();) {
		Timer* obj = *iter;
		if (obj->expirated()) {
			respawnOrange();
			iter = _timers.erase(iter);
			delete obj;
		}
		else {
			obj->incTime(delta_t);
			++iter;
		}
	}
}

void GameManager::respawnOrange()
{
	double x = randomDouble(20.0, 1.0);
	double y = randomDouble(20.0, 1.0);
	_dynamicObjects.push_back(new Orange(x, y, ZPLANE));

}

void GameManager::checkCollisions()
{
	_roadSide->collision(rodolfo);

	for each(DynamicObject* o in _dynamicObjects) {
		o->collision(rodolfo);
	}

}

void GameManager::createLights() 
{
	/* Como é direcional a position representa o vector para onde aponta o raio paralelo */
	Vector4 lightPosition = Vector4(0, 2, 10.0, 0.0);
	Vector4 ambientLight = Vector4(0.2, 0.2, 0.2, 1.0);
	Vector4 diffuseLight = Vector4(0.5, 0.5, 0.5, 1.0);
	Vector4 specularLight = Vector4(0.5, 0.5, 0.5, 1.0);

	_lightSources.push_back(new LightSource(0, lightPosition,ambientLight, diffuseLight, specularLight));
	
	int nlamps = 0;
	if (N_LAMPS > 5)
		nlamps = 5;
	else
		nlamps = N_LAMPS;
	
	Vector4 lampPosition = Vector4(0.0, 0.0, 0.0, 0.0);
	Vector4 lampAmbient = Vector4(0.4, 0.4, 0.4, 1.0);
	Vector4 lampDiffuse = Vector4(0.6, 0.6, 0.6, 1.0);
	Vector4 lampSpecular = Vector4(1.0, 1.0, 1.0, 1.0);

	double M_PI = PI;
	int count = 1;
	for (double i = 0; i < 2 * M_PI; i += M_PI * 2 / nlamps) {
		double x = cos(i) * INT_RAND(5,6);
		double y = sin(i) * INT_RAND(5,6);
		lampPosition.set(x, y, ZPLANE, 1.0);
		_lightSources.push_back(new Lamp(count, lampPosition, lampAmbient, lampDiffuse, lampSpecular));
		count++;
	}

}

void GameManager::showMessage(int message) {
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 20, 0, 20, 1, 30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, _textures[message]);

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glTexCoord2f(0.1, 1);
	glVertex3f(5, 15, ZPLANE);
	glTexCoord2f(1, 1);
	glVertex3f(15, 15, ZPLANE);
	glTexCoord2f(1, 0);
	glVertex3f(15, 5, ZPLANE);
	glTexCoord2f(0.1, 0);
	glVertex3f(5, 5, ZPLANE);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void GameManager::gameOver() {
	if (rodolfo->getLives() == 0) {
		// O Jogador perdeu
		_go = true;
	}
}

void GameManager::restart() {
	rodolfo->reset();
	delete _roadSide;
	for each(DynamicObject* d in _dynamicObjects) {
		delete d;
	}
	_dynamicObjects.erase(_dynamicObjects.begin(), _dynamicObjects.begin() + _dynamicObjects.size());
	for each(Timer* t in _timers) {
		delete t;
	}
	_timers.erase(_timers.begin(), _timers.begin() + _timers.size());
	createEnvironment();
	_go = false;
}

void GameManager::iterateLives() {
	GLboolean lightsOn[8] = { false };
	for (int i = 0; i < 8; i++) {
		lightsOn[i] = glIsEnabled(GL_LIGHT0 + i);
		if (lightsOn[i])
			cout << i << endl;
	}
	
	GLboolean wasOn;
	wasOn = glIsEnabled(GL_LIGHTING);

	glDisable(GL_LIGHTING);

	Car carro = Car(false);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 20, 0, 20, -2, 30);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(19, 19, 1);
	for (int i = 0; i < rodolfo->getLives(); i++) {
		glPushMatrix();
		glTranslated(-i*1.5, 0.0, 0.0);
		carro.instanceCar();
		glPopMatrix();
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	if (wasOn)
		glEnable(GL_LIGHTING);

	for (int i = 0; i < 8; i++) {
		if(lightsOn[i])
			glEnable(GL_LIGHT0 + i);
	}

}