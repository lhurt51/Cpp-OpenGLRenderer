#pragma once

#include "../Core/Utils/Math/MathUtils.h"
#include "BoundingSphere.h"

class Plane
{

	const Vector3f	m_normal;
	const float		m_distance;

public:

	Plane(const Vector3f& normal, float distance) : m_normal(normal), m_distance(distance)
	{}

	inline const Vector3f& GetNormal() const { return m_normal; }
	inline float GetDistance() const { return m_distance; }

	Plane Normalized() const;
	IntersectData IntersectSphere(const BoundingSphere& other) const;

};