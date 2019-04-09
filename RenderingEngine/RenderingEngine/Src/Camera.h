#pragma once

#include "Utils\Math\MathUtils.h"
#include "GameComponent.h"

class Camera : public GameComponent
{

	Matrix4f m_projection;

public:

	Camera(const Matrix4f& projection);

	Matrix4f GetViewProjection() const;
	virtual void AddToEngine(CoreEngine* engine);

};