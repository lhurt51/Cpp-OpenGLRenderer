#include "BoundingSphere.h"
#include <cassert>

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere & other)
{
	float radiusDistance = m_radius + other.m_radius;
	float centerDistance = (other.GetCenter() - m_center).Length();
	float distance = centerDistance - radiusDistance;

	return IntersectData(distance < 0, distance);
}

void BoundingSphere::Test()
{
	BoundingSphere sphere1(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	BoundingSphere sphere2(Vector3f(0.0f, 3.0f, 0.0f), 1.0f);
	BoundingSphere sphere3(Vector3f(0.0f, 0.0f, 2.0f), 1.0f);
	BoundingSphere sphere4(Vector3f(1.0f, 0.0f, 0.0f), 1.0f);

	IntersectData sphere1IntersectSphere2 = sphere1.IntersectBoundingSphere(sphere2);
	IntersectData sphere1IntersectSphere3 = sphere1.IntersectBoundingSphere(sphere3);
	IntersectData sphere1IntersectSphere4 = sphere1.IntersectBoundingSphere(sphere4);

	assert(sphere1IntersectSphere2.GetDoesIntersect() == false);
	assert(sphere1IntersectSphere2.GetDistance() == 1.0f);

	assert(sphere1IntersectSphere3.GetDoesIntersect() == false);
	assert(sphere1IntersectSphere3.GetDistance() == 0.0f);

	assert(sphere1IntersectSphere4.GetDoesIntersect() == true);
	assert(sphere1IntersectSphere4.GetDistance() == -1.0f);

	/*
	std::cout << "Sphere1 intersect Sphere2: " << sphere1IntersectSphere2.GetDoesIntersect() << ", Distance: " << sphere1IntersectSphere2.GetDistance() << std::endl;
	std::cout << "Sphere1 intersect Sphere3: " << sphere1IntersectSphere3.GetDoesIntersect() << ", Distance: " << sphere1IntersectSphere3.GetDistance() << std::endl;
	std::cout << "Sphere1 intersect Sphere4: " << sphere1IntersectSphere4.GetDoesIntersect() << ", Distance: " << sphere1IntersectSphere4.GetDistance() << std::endl;
	*/
}
