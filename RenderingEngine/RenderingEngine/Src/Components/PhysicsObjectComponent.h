#pragma once

#include "../Core/ECS/GameComponent.h"
#include "../Physics/PhysicsEngine.h"

class PhysicsObjectComponent : public GameComponent
{

	const PhysicsObject* m_physicsObject;

public:

	PhysicsObjectComponent(const PhysicsObject* object) : m_physicsObject(object)
	{}

	virtual void Update(float delta);

};