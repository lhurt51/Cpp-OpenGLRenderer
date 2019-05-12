#pragma once

#include "../Core/Utils/Math/MathUtils.h"
#include "Collider.h"

class BoundingSphere : public Collider
{

	Vector3f	m_center;
	float		m_radius;

public:

	BoundingSphere(const Vector3f& center, float radius) : Collider(Collider::TYPE_SPHERE),
		m_center(center),
		m_radius(radius)
	{}

	inline float GetRadius()			const { return m_radius; }

	IntersectData IntersectBoundingSphere(const BoundingSphere& other);

	virtual void Transform(const Vector3f& translation);
	virtual Vector3f GetCenter()		const { return m_center; }

	static void Test();

};