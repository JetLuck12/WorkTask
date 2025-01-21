#include "Intersection_manager.h"

#define epsilon 1e-5

std::optional<Segment3D> Intersection_manager::Intersect(const Segment3D& first, const Segment3D& second)
{
	if (fabs(Intersection_manager::get_determinant(first, second)) > epsilon)
	{
		return std::optional<Segment3D>{};
	}

	Vector3D v1 = first.get_start_vector();
	Vector3D v2 = first.get_end_vector();
	Vector3D v3 = second.get_start_vector();
	Vector3D v4 = second.get_end_vector();

	if (fabs(vector_mult(v2-v1,v4-v3)) < epsilon)
	{
		Vector3D u = v4 - v3 - v2 + v1;
		
		double t1 = 0;  
		double t2 = u.get_length();  

		double s1 = scalar_mult(v3 - v1, u) / t2;
		double s2 = vector_mult(v4-v1, u) / t2;

		if (s1 > s2) std::swap(s1, s2);

		double a1 = std::max(t1, s1);
		double a2 = std::min(t2, s2);

		if (a1 > a2)
		{
			return std::optional<Segment3D>{};
		}
		Vector3D intersectionStart = v1 + u * (a1 / t2);
		Vector3D intersectionEnd = v1 + u * (a2 / t2);

		return Segment3D{ intersectionStart, intersectionEnd };
	}

	double u =	((v4.get_x() - v2.get_x()) * (v4.get_y() - v3.get_y()) - 
				(v4.get_x() - v3.get_x()) * (v4.get_y() - v2.get_y())) /
				((v1.get_x() - v2.get_x()) * (v4.get_y() - v3.get_y()) - 
				(v4.get_x() - v3.get_x()) * (v1.get_y() - v2.get_y()));

	if (u < 0 || u > 1)
	{
		return std::optional<Segment3D>{};
	}

	double v =	((v1.get_x() - v2.get_x()) * (v4.get_y() - v2.get_y()) - 
				(v4.get_x() - v2.get_x()) * (v1.get_y() - v2.get_y())) /
				((v1.get_x() - v2.get_x()) * (v4.get_y() - v3.get_y()) - 
				(v4.get_x() - v3.get_x()) * (v1.get_y() - v2.get_y()));

	if (v < 0 || v > 1)
	{
		return std::optional<Segment3D>{};
	}
	return Segment3D{ {	u * (v1.get_x() - v2.get_x()) + v2.get_x(),
						u * (v1.get_y() - v2.get_y()) + v2.get_y(),
						u * (v1.get_z() - v2.get_z()) + v2.get_z()} ,
				{	u * (v1.get_x() - v2.get_x()) + v2.get_x(),
						u * (v1.get_y() - v2.get_y()) + v2.get_y(),
						u * (v1.get_z() - v2.get_z()) + v2.get_z()}
	};
}

double Intersection_manager::get_determinant(const Segment3D& first, const Segment3D& second)
{
	Vector3D v1 = first.get_start_vector();
	Vector3D v2 = first.get_end_vector();
	Vector3D v3 = second.get_start_vector();
	Vector3D v4 = second.get_end_vector();

	return	(v2.get_x()-v1.get_x())*(
				(v3.get_y()-v1.get_y())*(v4.get_z()-v1.get_z())-
				(v3.get_z()-v1.get_z())*(v4.get_y()-v1.get_y())
			)-
			(v2.get_y()-v1.get_y())*(
				(v3.get_x()-v1.get_x())*(v4.get_z()-v1.get_z())- 
				(v3.get_z()-v1.get_z())*(v4.get_x()-v1.get_x())
			)+
			(v2.get_z()-v1.get_z())*(
				(v3.get_x()-v1.get_x())*(v4.get_y()-v1.get_y())- 
				(v3.get_y()-v1.get_y())*(v4.get_x()-v1.get_x()));
}

double Intersection_manager::vector_mult(const Vector3D& first, const Vector3D& second)
{
	
	Vector3D vector_prod{
		first.get_y()* second.get_z() - first.get_z() * second.get_y(),
		first.get_z()* second.get_x() - first.get_x() * second.get_z(),
		first.get_x() * second.get_y() - first.get_y() * second.get_x()
	};
	return pow(vector_prod.get_x(), 2) + pow(vector_prod.get_y(), 2) + pow(vector_prod.get_z(), 2);
}

double Intersection_manager::scalar_mult(const Vector3D& first, const Vector3D& second)
{
	return first.get_x() * second.get_x() + first.get_y() * second.get_y() + first.get_z() * second.get_z();
}
