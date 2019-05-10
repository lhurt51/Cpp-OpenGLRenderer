#include "AABB.h"

#include <cassert>

IntersectData AABB::IntersectAABB(const AABB& other) const
{
	Vector3f distances1 = other.GetMinExtents() - m_maxExtents;
	Vector3f distances2 = m_minExtents - other.GetMaxExtents();
	Vector3f distances = Vector3f(distances1.Max(distances2));

	float maxDistance = distances.Max();
	return IntersectData(maxDistance < 0, maxDistance);
}

void AABB::Test()
{
	AABB aabb1(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
	AABB aabb2(Vector3f(1.0f, 1.0f, 1.0f), Vector3f(2.0f, 2.0f, 2.0f));
	AABB aabb3(Vector3f(1.0f, 0.0f, 0.0f), Vector3f(2.0f, 1.0f, 1.0f));
	AABB aabb4(Vector3f(0.0f, 0.0f, -2.0f), Vector3f(1.0f, 1.0f, -1.0f));
	AABB aabb5(Vector3f(0.0f, 0.5f, 0.0f), Vector3f(1.0f, 1.5f, 1.0f));
	AABB aabb6(Vector3f(0.3f, 0.5f, 0.7f), Vector3f(1.3f, 1.5f, 1.7f));

	IntersectData aabb1Intersectaabb2 = aabb1.IntersectAABB(aabb2);
	IntersectData aabb1Intersectaabb3 = aabb1.IntersectAABB(aabb3);
	IntersectData aabb1Intersectaabb4 = aabb1.IntersectAABB(aabb4);
	IntersectData aabb1Intersectaabb5 = aabb1.IntersectAABB(aabb5);
	IntersectData aabb1Intersectaabb6 = aabb1.IntersectAABB(aabb6);

	assert(aabb1Intersectaabb2.GetDoesIntersect() == false);
	assert(aabb1Intersectaabb2.GetDistance() == 0.0f);
	
	assert(aabb1Intersectaabb3.GetDoesIntersect() == false);
	assert(aabb1Intersectaabb3.GetDistance() == 0.0f);

	assert(aabb1Intersectaabb4.GetDoesIntersect() == false);
	assert(aabb1Intersectaabb4.GetDistance() == 1.0f);

	assert(aabb1Intersectaabb5.GetDoesIntersect() == true);
	assert(aabb1Intersectaabb5.GetDistance() == -0.5f);

	assert(aabb1Intersectaabb6.GetDoesIntersect() == true);
	assert(aabb1Intersectaabb6.GetDistance() == -0.3f);
	/*
	std::cout << "AABB1 intersect AABB2: " << aabb1Intersectaabb2.GetDoesIntersect() << ", Distance: " << aabb1Intersectaabb2.GetDistance() << std::endl;
	std::cout << "AABB1 intersect AABB3: " << aabb1Intersectaabb3.GetDoesIntersect() << ", Distance: " << aabb1Intersectaabb3.GetDistance() << std::endl;
	std::cout << "AABB1 intersect AABB4: " << aabb1Intersectaabb4.GetDoesIntersect() << ", Distance: " << aabb1Intersectaabb4.GetDistance() << std::endl;
	std::cout << "AABB1 intersect AABB5: " << aabb1Intersectaabb5.GetDoesIntersect() << ", Distance: " << aabb1Intersectaabb5.GetDistance() << std::endl;

	std::cout << std::endl;
	*/
}
