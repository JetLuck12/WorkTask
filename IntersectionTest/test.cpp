#include "pch.h"

#include "exceptions.h"
#include "Intersection_manager.h"
#include "Segment3D.h"

TEST(NonIntersect3D, Test1)
{
	Segment3D seg1{ Vector3D{0,0,0}, Vector3D{1,1,1} };
	Segment3D seg2{ Vector3D{2,2,2}, Vector3D{3,3,3} };
	ASSERT_THROW(Intersection_manager::Intersect(seg1, seg2), CollinearExp);
}

TEST(NonIntersect3D, Test2)
{
	Segment3D seg1{ Vector3D{0,0,0}, Vector3D{1,0,0} };
	Segment3D seg2{ Vector3D{0,1,0}, Vector3D{1,1,0} };
	ASSERT_THROW(Intersection_manager::Intersect(seg1, seg2), NotIntersect);
}

TEST(NonIntersect3D, Test3)
{
	Segment3D seg1{ Vector3D{0,0,0}, Vector3D{0,0,1} };
	Segment3D seg2{ Vector3D{0,1,0}, Vector3D{1,1,0} };
	ASSERT_THROW(Intersection_manager::Intersect(seg1, seg2), NotIntersect);
}

TEST(Intersect3D, Test1)
{
	Segment3D seg1{ Vector3D{0,0,0}, Vector3D{1.0,1.0,1.0} };
	Segment3D seg2{ Vector3D{1.0,0.0,0.0}, Vector3D{0.0,1.0,1.0} };
	std::optional<Vector3D> intersect_point = Intersection_manager::Intersect(seg1, seg2);
	ASSERT_TRUE(intersect_point.has_value());
}

TEST(Intersect3D, Test2)
{
	Segment3D seg1{ Vector3D{0.5,0.5,0.0}, Vector3D{0.5,0.5,1.0} };
	Segment3D seg2{ Vector3D{0.5,0.0,0.5}, Vector3D{0.5,1.0,0.5} };
	std::optional<Vector3D> intersect_point = Intersection_manager::Intersect(seg1, seg2);
	ASSERT_TRUE(intersect_point.has_value());
}

TEST(Intersect3D, Test3)
{
	Segment3D seg1{ Vector3D{0.0,0.0,0.0}, Vector3D{2.0,2.0,2.0} };
	Segment3D seg2{ Vector3D{1.0,0.0,1.0}, Vector3D{1.0,2.0,1.0} };
	std::optional<Vector3D> intersect_point = Intersection_manager::Intersect(seg1, seg2);
	ASSERT_TRUE(intersect_point.has_value());
}

TEST(Intersect3D, Test4)
{
	Segment3D seg1{ Vector3D{0.0,0.0,0.0}, Vector3D{1.0,0.0,1.0} };
	Segment3D seg2{ Vector3D{0.5,0.0,0.5}, Vector3D{0.5,1.0,0.5} };
	std::optional<Vector3D> intersect_point = Intersection_manager::Intersect(seg1, seg2);
	ASSERT_TRUE(intersect_point.has_value());
}

TEST(Intersect3D, Test5)
{
	Segment3D seg1{ Vector3D{1.0,1.0,1.0}, Vector3D{3.0,3.0,3.0} };
	Segment3D seg2{ Vector3D{2.0,2.0,2.0}, Vector3D{2.0,2.0,4.0} };
	std::optional<Vector3D> intersect_point = Intersection_manager::Intersect(seg1, seg2);
	ASSERT_TRUE(intersect_point.has_value());
}

TEST(Intersect2D, Test1)
{
	Segment3D seg1{ Vector3D{0.0,0.0,0.0}, Vector3D{1.0,1.0,0.0} };
	Segment3D seg2{ Vector3D{1.0,1.0,0.0}, Vector3D{2.0,2.0,0.0} };
	ASSERT_THROW(Intersection_manager::Intersect(seg1, seg2), CollinearExp);
}

TEST(Intersect2D, Test2)
{
	Segment3D seg1{ Vector3D{0.0,0.0,0.0}, Vector3D{2.0,0.0,0.0} };
	Segment3D seg2{ Vector3D{1.0,-1.0,0.0}, Vector3D{1.0,1.0,0.0} };
	std::optional<Vector3D> intersect_point = Intersection_manager::Intersect(seg1, seg2);
	ASSERT_TRUE(intersect_point.has_value());
}

TEST(Intersect2D, Test3)
{
	Segment3D seg1{ Vector3D{0.0,0.0,0.0}, Vector3D{2.0,2.0,0.0} };
	Segment3D seg2{ Vector3D{1.0,0.0,0.0}, Vector3D{0.0,1.0,0.0} };
	std::optional<Vector3D> intersect_point = Intersection_manager::Intersect(seg1, seg2);
	ASSERT_TRUE(intersect_point.has_value());
}

TEST(Intersect2D, Test4)
{
	Segment3D seg1{ Vector3D{0.0,0.0,0.0}, Vector3D{3.0,3.0,0.0} };
	Segment3D seg2{ Vector3D{2.0,0.0,0.0}, Vector3D{0.0,2.0,0.0} };
	std::optional<Vector3D> intersect_point = Intersection_manager::Intersect(seg1, seg2);
	ASSERT_TRUE(intersect_point.has_value());
}

TEST(Intersect2D, Test5)
{
	Segment3D seg1{ Vector3D{0.5,0.5,0.0}, Vector3D{1.5,0.5,0.0} };
	Segment3D seg2{ Vector3D{1.0,0.0,0.0}, Vector3D{1.0,1.0,0.0} };
	std::optional<Vector3D> intersect_point = Intersection_manager::Intersect(seg1, seg2);
	ASSERT_TRUE(intersect_point.has_value());
}