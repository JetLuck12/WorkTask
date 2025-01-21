#include "Vector3D.h"

double Vector3D::get_x() const
{
	return X;
}

double Vector3D::get_y() const
{
	return Y;
}

double Vector3D::get_z() const
{
	return Z;
}

Vector3D& Vector3D::operator+(const Vector3D& vec)
{
		X += vec.get_x();
		Y += vec.get_y();
		Z += vec.get_z();
		return *this;
}

Vector3D& Vector3D::operator-(const Vector3D& vec)
{
	X -= vec.get_x();
	Y -= vec.get_y();
	Z -= vec.get_z();
	return *this;
}

double Vector3D::get_length() const
{
	return X * X + Y * Y + Z * Z;
}

Vector3D& Vector3D::operator*(double a)
{
	X *= a;
	Y *= a;
	Z *= a;
	return *this;
}

