#include "Texture.h"

#define NUMBER_TEX 3
#define	TEX_H 512
using namespace std;
Texture::Texture()
{
}


Texture::~Texture()
{
}


GLuint* Texture::loadTexture(char** pathnames, int size)
{
	GLuint *textures = new GLuint[NUMBER_TEX];
	glGenTextures(NUMBER_TEX, textures);
	FILE *fp;
	unsigned char* data1;
	unsigned char* header;
	for (int i = 0; i < size; i++) {

		fopen_s(&fp, pathnames[i], "rb");
		if (fp == NULL) {
			cout << pathnames[0] << endl;
			Sleep(50000);
			exit(-1);
		}
		header = (unsigned char *)malloc(54 * sizeof(unsigned char));

		if (fread(header, sizeof(unsigned char), 54, fp) != 54) {
			cout << "Error reading header" << endl;
			Sleep(50000);
			exit(-1);
		}
		
		if (header[0] != 'B' || header[1] != 'M') {
			cout << "Not a correct BMP file" << endl;
			Sleep(50000);
			exit(-1);
		}
		
		unsigned int width = *(unsigned int*)&(header[0x12]);
		unsigned int height = *(unsigned int*)&(header[0x16]);


		if (width != height || (width % 2 != 0) || (height % 2 != 0)) {
			// If the image does not have a valid size
			cout << "Invalid image size. Width: " << width << " Height:" << height << endl;
			Sleep(50000);
			exit(-1);
		}
		
		int size =  width * height * 3;
		int area = width * height;

		data1 = (unsigned char *)malloc(size);
		
		fread(data1, sizeof(unsigned char), size, fp);
		fclose(fp);

		for (int i = 0; i < area; ++i)
		{
			int index = i * 3;
			unsigned char B, R;
			B = data1[index];
			R = data1[index + 2];

			data1[index] = R;
			data1[index + 2] = B;

		}


		glBindTexture(GL_TEXTURE_2D, textures[i]);
		
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TEX_H, TEX_H, GL_RGB, GL_UNSIGNED_BYTE, data1);
		free(data1);
		free(header);
	}
	
	return textures;

}
