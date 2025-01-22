#include "Intersection_manager.h"
#include "exceptions.h"

#define epsilon 1e-5

std::optional<Vector3D> Intersection_manager::Intersect(const Segment3D& first, const Segment3D& second)
{
	//if determinant is zero - vectors are not coplanar
	if (fabs(Intersection_manager::get_determinant(first, second)) > epsilon)
	{
		throw NotIntersect{};
	}

	Vector3D v1 = first.get_start_vector();
	Vector3D v2 = first.get_end_vector();
	Vector3D v3 = second.get_start_vector();
	Vector3D v4 = second.get_end_vector();

	//check collinearity
	Vector3D n1 = (v2 - v1).normalize();
	Vector3D n2 = (v4 - v3).normalize();
	if (fabs(n1.get_x()-n2.get_x())< epsilon && 
		fabs(n1.get_y() - n2.get_y()) < epsilon && 
		fabs(n1.get_z() - n2.get_z()) < epsilon)
	{
		throw CollinearExp{};
	}

	//find intersect point for first segment
	double u =	((v4.get_x() - v2.get_x()) * (v4.get_y() - v3.get_y()) - 
				(v4.get_x() - v3.get_x()) * (v4.get_y() - v2.get_y())) /
				((v1.get_x() - v2.get_x()) * (v4.get_y() - v3.get_y()) - 
				(v4.get_x() - v3.get_x()) * (v1.get_y() - v2.get_y()));


	//if u < 0 or u > 1 - point is outside of segment
	if (u < 0 || u > 1)
	{
		throw NotIntersect{};
	}


	//find intersect point for second segment
	double v =	((v1.get_x() - v2.get_x()) * (v4.get_y() - v2.get_y()) - 
				(v4.get_x() - v2.get_x()) * (v1.get_y() - v2.get_y())) /
				((v1.get_x() - v2.get_x()) * (v4.get_y() - v3.get_y()) - 
				(v4.get_x() - v3.get_x()) * (v1.get_y() - v2.get_y()));

	//if v < 0 or v > 1 - point is outside of segment
	if (v < 0 || v > 1)
	{
		throw NotIntersect{};
	}
	return Vector3D{	u * (v1.get_x() - v2.get_x()) + v2.get_x(),
						u * (v1.get_y() - v2.get_y()) + v2.get_y(),
						u * (v1.get_z() - v2.get_z()) + v2.get_z()
	};
}

double Intersection_manager::get_determinant(const Segment3D& first, const Segment3D& second)
{
	//return determinant of two segments (coplanar check)
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