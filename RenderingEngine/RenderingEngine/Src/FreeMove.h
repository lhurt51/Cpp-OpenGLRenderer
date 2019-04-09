#pragma once

#include "Utils\Math\MathUtils.h"
#include "GameComponent.h"
#include "Input\Input.h"

class FreeMove : public GameComponent
{

	float m_speed;
	int m_forwardKey;
	int m_backKey;
	int m_leftKey;
	int m_rightKey;

public:

	FreeMove(float speed = 10.0f, int forwardKey = Input::KEY_W, int backKey = Input::KEY_S, int leftKey = Input::KEY_A, int rightKey = Input::KEY_D);

	virtual void Input(float delta);

private:

	void Move(const Vector3f& direction, float amt);

};

