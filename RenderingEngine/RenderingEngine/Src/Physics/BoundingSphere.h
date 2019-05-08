#pragma once

#include "../Core/Utils/Math/MathUtils.h"
#include "IntersectData.h"

class BoundingSphere
{

	const Vector3f	m_center;
	const float		m_radius;

public:

	BoundingSphere(const Vector3f& center, float radius) :
		m_center(center),
		m_radius(radius)
	{}

	inline const Vector3f& GetCenter()	const { return m_center; }
	inline float GetRadius()			const { return m_radius; }

	IntersectData IntersectBoundingSphere(const BoundingSphere& other);

};