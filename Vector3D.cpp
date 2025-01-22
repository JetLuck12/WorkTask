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

double Vector3D::length()
{
	return X * X + Y * Y + Z * Z;
}

Vector3D Vector3D::normalize()
{
	double len = length();
	return { X / len, Y / len, Z / len };
}

Vector3D Vector3D::operator-(const Vector3D& vec) const
{
	return Vector3D{ X - vec.get_x(), Y - vec.get_y(), Z - vec.get_z() };
}
