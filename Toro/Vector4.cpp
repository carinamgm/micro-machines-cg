#include "Vector4.h"


Vector4::Vector4(double x, double y, double z, double w) : _w(w), Vector3(x, y, z)
{
}


Vector4::~Vector4()
{
}

double Vector4::getW() const
{
	return _w;
}


void Vector4::set(double x,double y,double z,double w)
{
	_w = w;
	Vector3::set(x, y, z);
}

Vector4 Vector4::operator=(const Vector4& vec) 
{
	_w = vec.getW();
	Vector3::operator=(vec);
	return *this;
}

Vector4 Vector4::operator*(double num)
{
	_w = getW()*num;
	Vector3::operator*(num);
	return *this;
}

Vector4 Vector4::operator+(const Vector4& vec)
{
	_w += vec.getW();
	Vector3::operator+(vec);
	return *this;
}

Vector4 Vector4::operator-(const Vector4& vec) 
{
	_w -= vec.getW();
	Vector3::operator-(vec);
	return *this;
}