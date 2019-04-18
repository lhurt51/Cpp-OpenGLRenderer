#pragma once

#include "Utils\Math\MathUtils.h"
#include "GameComponent.h"

class Camera : public GameComponent
{

	Matrix4f m_projection;

public:

	Camera(const Matrix4f& projection);

	Matrix4f GetViewProjection() const;

	inline void SetProjection(const Matrix4f& projection) { m_projection = projection; }
	virtual void AddToEngine(CoreEngine* engine);

};