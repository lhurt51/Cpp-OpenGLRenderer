#include "PhysicsEngine.h"

void PhysicsEngine::AddObject(const PhysicsObject& object)
{
	m_objects.push_back(object);
}

void PhysicsEngine::Simulate(float delta)
{
	for (PhysicsObject& object : m_objects)
	{
		object.Integrate(delta);
	}
}
