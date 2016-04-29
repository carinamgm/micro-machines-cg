#include "Material.h"



Material::Material(GLfloat *amb, GLfloat *dif, GLfloat *spec, GLfloat shi): _shin(shi)
{
	for (int i = 0; i < 4; i++) {
		_amb[i] = amb[i];
		_diff[i] = dif[i];
		_spec[i] = spec[i];
	}

}


Material::~Material()
{
}


void Material::applyMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shin);
}
