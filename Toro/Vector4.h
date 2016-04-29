#pragma once
#include "Vector3.h"
class Vector4 :
	public Vector3
{
public:
	Vector4(double x, double y, double z, double w);
	virtual ~Vector4();
protected:
	double _w;
private:
	Vector3 _vector3;
public:
	double getW() const;
	Vector4 operator*(double num);
	void set(double x, double y, double z, double w);
	Vector4 operator=(const Vector4& vec);
	Vector4 operator+(const Vector4& vec);
	Vector4 operator-(const Vector4& vec);
};

