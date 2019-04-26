#pragma once

#include "Utils\Math\MathUtils.h"
#include "GameComponent.h"

class Camera
{

	Matrix4f	m_projection;
	Transform*	m_transform;

public:

	Camera(const Matrix4f& projection, Transform* transform) : m_projection(projection), m_transform(transform)
	{}

	inline Transform* GetTransform() { return m_transform; }
	inline const Transform& GetTransform() const { return *m_transform; }
	Matrix4f GetViewProjection() const;

	inline void SetProjection(const Matrix4f& projection) { m_projection = projection; }
	inline void SetTransform(Transform* transform) { m_transform = transform; }

};

class CameraComponent : public GameComponent
{

	Camera m_camera;

public:

	CameraComponent(const Matrix4f projection) : m_camera(projection, 0)
	{}

	virtual void AddToEngine(CoreEngine* engine) const;

	inline Matrix4f GetViewProjection() const { return m_camera.GetViewProjection(); }

	inline void SetProjection(const Matrix4f& projection) { m_camera.SetProjection(projection); }
	virtual void SetParent(GameObject* parent);
	
};