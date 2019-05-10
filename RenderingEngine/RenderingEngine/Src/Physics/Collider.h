#pragma once

#include "IntersectData.h"

class Collider
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

	Collider(int type) : m_type(type)
	{}

	inline int GetType() const { return m_type; }

	IntersectData Intersect(const Collider& other);

};