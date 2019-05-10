#include "PhysicsEngine.h"
#include "BoundingSphere.h"

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

void PhysicsEngine::HandleCollisions()
{
	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		for (unsigned int j = i + 1; j < m_objects.size(); j++)
		{
			IntersectData intersectData = m_objects[i].GetBoundingSphere().Intersect(m_objects[j].GetBoundingSphere());

			if (intersectData.GetDoesIntersect())
			{
				m_objects[i].SetVelocity(m_objects[i].GetVelocity() * -1);
				m_objects[j].SetVelocity(m_objects[j].GetVelocity() * -1);
			}
		}
	}
}
