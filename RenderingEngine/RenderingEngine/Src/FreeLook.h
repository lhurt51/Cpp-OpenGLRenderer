#pragma once

#include "Utils\Math\MathUtils.h"
#include "GameComponent.h"
#include "Input\Input.h"

class FreeLook : public GameComponent
{

	float		m_sensitivity;
	int			m_unlockMouseKey;
	bool		m_mouseLocked;
	Vector2f	m_windowCenter;

public:

	FreeLook(const Vector2f& windowCenter, float sensitivity = 0.02f, int unlockMouseKey = Input::KEY_ESCAPE) :
		m_sensitivity(sensitivity), m_unlockMouseKey(unlockMouseKey), m_mouseLocked(false), m_windowCenter(windowCenter)
	{}

	virtual void ProcessInput(const Input& input, float delta);

};

