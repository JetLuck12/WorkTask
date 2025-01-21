#pragma once
#include "Vector3D.h"

class Segment3D final
{
public:
	Segment3D(const Vector3D& start_, const Vector3D& end_):start(start_), end(end_){}
	Segment3D(const Segment3D& seg) = default;
	Segment3D& operator=(const Segment3D& seg) = default;
	~Segment3D() = default;
	const Vector3D& get_start_vector() const;
	const Vector3D& get_end_vector() const;
	double get_length() const;
private:
	Vector3D start;
	Vector3D end;
};

