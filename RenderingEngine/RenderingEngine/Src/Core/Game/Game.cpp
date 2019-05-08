#include "Game.h"

#include <iostream>

#include "../../Rendering/RenderingEngine.h"

void Game::ProcessInput(const Input& input, float delta)
{
	m_inputTimer.StartInvocation();
	m_root.ProcessInputAll(input, delta);
	m_inputTimer.StopInvocation();
}

void Game::Update(float delta)
{
	m_updatetimer.StartInvocation();
	m_root.UpdateAll(delta);
	m_updatetimer.StopInvocation();
}

void Game::Render(RenderingEngine* renderingEngine)
{
	renderingEngine->Render(m_root);
}
