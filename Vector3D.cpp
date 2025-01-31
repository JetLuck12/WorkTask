#include "Vector3D.h"

#include <cmath>

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
	return pow(X * X + Y * Y + Z * Z, 0.5);
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

Vector3D Vector3D::v_mult(const Vector3D& vec) const
{
	return { Y * vec.get_z() - vec.get_y() * Z, -X * vec.get_z() + vec.get_x() * Z, X * vec.get_y() - vec.get_x() * Y };
}

Vector3D& Vector3D::operator*(double scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& vec) const
{
	return { X + vec.get_x(), Y + vec.get_y(), Z + vec.get_z() };
}

