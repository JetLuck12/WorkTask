#pragma once
#include <optional>
#include <vector>

#include "Segment3D.h"
#include "Vector3D.h"

class Intersection_manager
{
public:
	Intersection_manager() = delete;
	~Intersection_manager() = delete;
	static std::optional<Segment3D> Intersect(const Segment3D& first, const Segment3D& second);
private:
	static double get_determinant(const Segment3D& first, const Segment3D& second);
	static double vector_mult(const Vector3D& first, const Vector3D& second);
	static double scalar_mult(const Vector3D& first, const Vector3D& second);
};

