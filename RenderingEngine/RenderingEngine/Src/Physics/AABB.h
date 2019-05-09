#pragma once

#include "../Core/Utils/Math/MathUtils.h"
#include "IntersectData.h"

class AABB
{

	const Vector3f m_minExtents;
	const Vector3f m_maxExtents;

public:

	AABB(const Vector3f& minExtents, const Vector3f&  maxExtents) : m_minExtents(minExtents), m_maxExtents(maxExtents)
	{}

	IntersectData IntersectAABB(const AABB& other) const;

	inline const Vector3f& GetMinExtents() const { return m_minExtents; }
	inline const Vector3f& GetMaxExtents() const { return m_maxExtents; }

};
