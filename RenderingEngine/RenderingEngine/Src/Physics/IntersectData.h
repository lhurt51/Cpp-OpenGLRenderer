#pragma once

class IntersectData
{

	const bool	m_doesIntersect;
	const float m_distance;

public:

	IntersectData(const bool doesIntersect, const float distance) :
		m_doesIntersect(doesIntersect),
		m_distance(distance)
	{}

	inline bool GetDoesIntersect()	const { return m_doesIntersect; }
	inline float GetDistance()		const { return m_distance; }

};