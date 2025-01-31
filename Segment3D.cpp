#include "Segment3D.h"

const Vector3D& Segment3D::get_end_vector() const
{
	return end;
}

const Vector3D& Segment3D::get_start_vector() const
{
	return start;
}

Vector3D Segment3D::v_mult(const Segment3D& seg) const
{
	Vector3D vec1 = end - start;
	Vector3D vec2 = seg.get_end_vector() - seg.get_start_vector();
	return vec1.v_mult(vec2);
}
