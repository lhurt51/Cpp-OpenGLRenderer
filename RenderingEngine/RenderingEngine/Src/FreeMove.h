#pragma once

#include "Utils\Math\MathUtils.h"
#include "GameComponent.h"

class FreeMove : public GameComponent
{

	float m_speed;
	int m_forwardKey;
	int m_backKey;
	int m_leftKey;
	int m_rightKey;

public:

	FreeMove(float speed = 10.0f, int forwardKey = Input::KEY_W, int backKey = Input::KEY_S, int leftKey = Input::KEY_A, int rightKey = Input::KEY_D) :
		m_speed(speed), m_forwardKey(forwardKey), m_backKey(backKey), m_leftKey(leftKey), m_rightKey(rightKey)
	{}

	virtual void ProcessInput(const Input& input, float delta);

private:

	void Move(const Vector3f& direction, float amt);

};

