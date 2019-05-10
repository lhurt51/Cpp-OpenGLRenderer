#include "PhysicsObjectComponent.h"

void PhysicsObjectComponent::Update(float delta)
{
	GetTransform()->SetPos(m_physicsObject->GetPosition());
}
