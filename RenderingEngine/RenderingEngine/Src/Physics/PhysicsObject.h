#pragma once

#include "../Core/Utils/Math/MathUtils.h"

class PhysicsObject
{

	Vector3f m_position;
	Vector3f m_velocity;

public:

	PhysicsObject(const Vector3f& position, const Vector3f velocity) : m_position(position), m_velocity(velocity)
	{}

	inline const Vector3f& GetPosition() const { return m_position; }
	inline const Vector3f& GetVelocity() const { return m_velocity; }

	void Integrate(float delta);

	static void Test();

};

