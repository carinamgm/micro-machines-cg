#pragma once
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <GL/glut.h>
class Texture
{
public:
	Texture();
	virtual ~Texture();
	GLuint*  loadTexture(char** pathnames, int size);
};

