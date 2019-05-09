#include "AABB.h"

IntersectData AABB::IntersectAABB(const AABB& other) const
{
	Vector3f distances1 = other.GetMinExtents() - m_maxExtents;
	Vector3f distances2 = m_minExtents - other.GetMaxExtents();
	Vector3f distances = Vector3f(distances1.Max(distances2));

	float maxDistance = distances.Max();
	return IntersectData(maxDistance < 0, maxDistance);
}
