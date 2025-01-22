#pragma once
class Vector3D final
{
public:
	Vector3D(const double x, const double y, const double z) :X(x), Y(y), Z(z) {}
	Vector3D(const Vector3D& vec) = default;
	Vector3D& operator=(const Vector3D& vec) = default;
	Vector3D operator-(const Vector3D& vec) const;
	~Vector3D() = default;
	double get_x() const;
	double get_y() const;
	double get_z() const;
	Vector3D normalize();
	double length();
private:
	double X;
	double Y;
	double Z;
};

