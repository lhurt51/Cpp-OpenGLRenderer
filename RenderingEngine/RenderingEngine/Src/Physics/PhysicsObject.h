#pragma once

#include "../Core/Utils/Math/MathUtils.h"
#include "Collider.h"

class PhysicsObject
{

	Vector3f	m_position;
	Vector3f	m_oldPosition;
	Vector3f	m_velocity;
	Collider*	m_collider;

public:

	PhysicsObject(Collider* collider, const Vector3f& velocity) : m_position(collider->GetCenter()), m_oldPosition(collider->GetCenter()), m_velocity(velocity), m_collider(collider)
	{}
	PhysicsObject(const PhysicsObject& other);
	virtual ~PhysicsObject();

	void operator=(PhysicsObject other);

	inline const Vector3f& GetPosition() const { return m_position; }
	inline const Vector3f& GetVelocity() const { return m_velocity; }

	inline Collider& GetCollider()
	{
		Vector3f translation = m_position - m_oldPosition;
		m_oldPosition = m_position;
		m_collider->Transform(translation);
		return *m_collider;
	}

	inline void SetVelocity(const Vector3f& velocity) { m_velocity = velocity; }

	void Integrate(float delta);

	static void Test();

};

