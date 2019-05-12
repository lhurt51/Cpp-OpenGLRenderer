#pragma once

#include "../Core/Utils/Math/MathUtils.h"

class IntersectData
{

	const bool		m_doesIntersect;
	const Vector3f	m_direction;

public:

	IntersectData(const bool doesIntersect, const Vector3f& direction) :
		m_doesIntersect(doesIntersect),
		m_direction(direction)
	{}

	inline bool GetDoesIntersect()	const { return m_doesIntersect; }
	inline Vector3f GetDirection()	const { return m_direction; }
	inline float GetDistance()		const { return m_direction.Length(); }

};