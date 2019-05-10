#pragma once

#include "PhysicsObject.h"

#include <vector>

class PhysicsEngine
{

	std::vector<PhysicsObject> m_objects;

public:

	PhysicsEngine()
	{}

	void AddObject(const PhysicsObject& object);

	void Simulate(float delta);

	// Temporary code
	inline const PhysicsObject& GetObject(unsigned int index) const
	{
		return m_objects[index];
	}

	inline unsigned int GetNumObjects() const
	{
		return (unsigned int)m_objects.size();
	}

};