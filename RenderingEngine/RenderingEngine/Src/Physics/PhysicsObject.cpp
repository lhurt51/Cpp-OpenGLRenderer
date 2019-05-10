#include "PhysicsObject.h"

void PhysicsObject::Integrate(float delta)
{
	m_position += m_velocity * delta;
}
