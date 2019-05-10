#include "Collider.h"

#include "BoundingSphere.h"

#include <iostream>
#include <cstdlib>

IntersectData Collider::Intersect(const Collider & other)
{
	if (m_type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE)
	{
		BoundingSphere* self = (BoundingSphere*)this;
		return self->IntersectBoundingSphere((BoundingSphere&)other);
	}

	std::cerr << "Error: Collisions not implemented between specified colliders." << std::endl;
	exit(1);

	return IntersectData(false, 0);
}
