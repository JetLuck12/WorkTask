#include "Intersection_manager.h"
#include "exceptions.h"

#define epsilon 1e-5

std::optional<Vector3D> Intersection_manager::Intersect(const Segment3D& first, const Segment3D& second)
{
	Vector3D vec_product = first.v_mult(second);

	if (fabs(vec_product.length()) < epsilon)
	{
		//segments are parallel
		Segment3D seg{ {first.get_start_vector()}, {second.get_start_vector()} };
		Vector3D check_vec = seg.v_mult(first);
		if (fabs(check_vec.length()) > epsilon)
		{
			// segments not collinear
			throw NotIntersect{};
		}
		//segments collinear
		throw CollinearExp{};
	}

	if (!is_planar(first, second))
	{
		throw NotIntersect{};
	}

	//we have system of equations for u,v parameters, 2x3 sized, will try to solve it
	auto [u, v] = get_params(first, second);
	if (u < 0 || u > 1 || v < 0 || v > 1)
	{
		throw NotIntersect{};
	}
	return first.get_start_vector() + (first.get_end_vector() - first.get_start_vector()) * u;
}

double Intersection_manager::get_determinant(const std::vector<std::vector<double>>& matrix)
{
	//return determinant of matrix 2x2
	return	matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

std::pair<double, double> Intersection_manager::get_params(const Segment3D& first, const Segment3D& second)
{
	//try to solve system of equations by Kramer's method
	//a11 * u + a12 * v = c1
	//a21 * u + a22 * v = c2
	//a31 * u + a32 * v = c3
	Vector3D vec1_1 = first.get_start_vector();
	Vector3D vec1_2 = first.get_end_vector();
	Vector3D vec2_1 = second.get_start_vector();
	Vector3D vec2_2 = second.get_end_vector();

	//trying to fing good lines for system (det != 0)

	std::vector<std::vector<double>> left_part{ {vec1_2.get_x() - vec1_1.get_x(), - vec2_2.get_x() + vec2_1.get_x()},
											{vec1_2.get_y() - vec1_1.get_y(), - vec2_2.get_y() + vec2_1.get_y()} };

	double det = get_determinant(left_part);

	std::vector<std::vector<double>> u_part;
	std::vector<std::vector<double>> v_part;

	if (fabs(det) < epsilon)
	{
		//bad coords, trying other
		left_part = { {vec1_2.get_x() - vec1_1.get_x(), - vec2_2.get_x() + vec2_1.get_x()},
					{vec1_2.get_z() - vec1_1.get_z(), - vec2_2.get_z() + vec2_1.get_z()} };
		det = get_determinant(left_part);
		if (fabs(det) < epsilon)
		{
			// bad coords again, trying other
			left_part = { {vec1_2.get_y() - vec1_1.get_y(), - vec2_2.get_y() + vec2_1.get_y()},
						{vec1_2.get_z() - vec1_1.get_z(), - vec2_2.get_z() + vec2_1.get_z()} };

			u_part = { {vec2_1.get_y() - vec1_1.get_y(), - vec2_2.get_y() + vec2_1.get_y()},
						{vec2_1.get_z() - vec1_1.get_z(), - vec2_2.get_z() + vec2_1.get_z()} };

			v_part = { {vec1_2.get_y() - vec1_1.get_y(), vec2_1.get_y() - vec1_1.get_y()},
						{vec1_2.get_z() - vec1_1.get_z(), vec2_1.get_z() - vec1_1.get_z()} };


			// this det is not zero, otherwise segments are collinear
			det = get_determinant(left_part);
		}
		else
		{
			u_part = { {vec2_1.get_x() - vec1_1.get_x(), - vec2_2.get_x() + vec2_1.get_x()},
						{vec2_1.get_z() - vec1_1.get_z(), - vec2_2.get_z() + vec2_1.get_z()} };

			v_part = { {vec1_2.get_x() - vec1_1.get_x(), vec2_1.get_x() - vec1_1.get_x()},
						{vec1_2.get_z() - vec1_1.get_z(), vec2_1.get_z() - vec1_1.get_z()} };
		}
	}
	else
	{
		u_part = { {vec2_1.get_x() - vec1_1.get_x(), - vec2_2.get_x() + vec2_1.get_x()},
					{vec2_1.get_y() - vec1_1.get_y(), - vec2_2.get_y() + vec2_1.get_y()} };

		v_part = { {vec1_2.get_x() - vec1_1.get_x(), vec2_1.get_x() - vec1_1.get_x()},
					{vec1_2.get_y() - vec1_1.get_y(), vec2_1.get_y() - vec1_1.get_y()} };
	}

	return { get_determinant(u_part) / det, get_determinant(v_part) / det };
}

bool Intersection_manager::is_planar(const Segment3D& first, const Segment3D& second)
{
	Vector3D surf_norm = first.v_mult(second);
	return fabs(
		surf_norm.get_x() * (first.get_start_vector().get_x() - second.get_start_vector().get_x()) +
		surf_norm.get_y() * (first.get_start_vector().get_y() - second.get_start_vector().get_y()) +
		surf_norm.get_z() * (first.get_start_vector().get_z() - second.get_start_vector().get_z())
	) < epsilon;
}
