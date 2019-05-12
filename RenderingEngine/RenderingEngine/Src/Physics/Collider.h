#pragma once

#include "IntersectData.h"
#include "../Core/Utils/Math/MathUtils.h"
#include "../Core/Utils/AssetManager/ReferenceCounter.h"

class Collider : public ReferenceCounter
{
public:

	enum
	{
		TYPE_SPHERE,
		TYPE_AABB,
		TYPE_SIZE
	};

private:

	int m_type;

public:

	Collider(int type) : ReferenceCounter(), m_type(type)
	{}

	inline int GetType() const { return m_type; }

	IntersectData Intersect(const Collider& other);

	virtual void Transform(const Vector3f& translation) = 0;
	virtual Vector3f GetCenter() const { return Vector3f(0.0f, 0.0f, 0.0f); }

};