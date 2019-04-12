#pragma once

#include "Utils\Math\MathUtils.h"
#include "GameComponent.h"
#include "Input\Input.h"

class FreeLook : public GameComponent
{

	float m_sensitivity;
	int m_unlockMouseKey;

public:

	FreeLook(float sensitivity = 0.02f, int unlockMouseKey = Input::KEY_ESCAPE);

	virtual void Input(float delta);

};

