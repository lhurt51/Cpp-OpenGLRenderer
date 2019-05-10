#pragma once

#include "../Core/ECS/GameComponent.h"
#include "../Physics/PhysicsEngine.h"

class PhysicsEngineComponent : public GameComponent
{

	PhysicsEngine m_physicsEngine;

public:

	PhysicsEngineComponent(const PhysicsEngine& engine) : m_physicsEngine(engine)
	{}

	virtual void Update(float delta);

	inline const PhysicsEngine& GetPhysicsEngine() { return m_physicsEngine; }
};
