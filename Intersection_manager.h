#pragma once
#include <optional>
#include <vector>

#include "Segment3D.h"
#include "Vector3D.h"

//class for intersect check
class Intersection_manager final
{
public:
	Intersection_manager() = delete;
	~Intersection_manager() = delete;
	static std::optional<Vector3D> Intersect(const Segment3D& first, const Segment3D& second);
private:
	static double get_determinant(const std::vector<std::vector<double>>& matrix);
	static std::pair<double, double> get_params(const Segment3D& first, const Segment3D& second);
	static bool is_planar(const Segment3D& first, const Segment3D& second);
};

