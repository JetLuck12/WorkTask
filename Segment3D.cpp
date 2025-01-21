#include "Segment3D.h"

const Vector3D& Segment3D::get_end_vector() const
{
	return end;
}

const Vector3D& Segment3D::get_start_vector() const
{
	return start;
}

double Segment3D::get_length() const
{
	Vector3D vec{ end.get_x() - start.get_x(),end.get_y() - start.get_y() ,end.get_z() - start.get_z() };
	return vec.get_length();
}
