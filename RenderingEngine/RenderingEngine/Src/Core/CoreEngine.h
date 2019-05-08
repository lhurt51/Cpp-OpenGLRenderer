#pragma once

#include <string>

#include "..\Rendering\RenderingEngine.h"

class Game;

class CoreEngine
{

	ProfileTimer		m_sleepTimer;
	ProfileTimer		m_windowUpdateTimer;
	ProfileTimer		m_swapBufferTimer;

	bool				m_isRunning;
	double				m_frameTime;
	Window*				m_window;
	RenderingEngine*	m_renderingEngine;
	Game*				m_game;

public:

	CoreEngine(double frameRate, Window* window, RenderingEngine* renderingEngine, Game* game);

	void Start();
	void Stop();

	inline RenderingEngine* GetRenderingEngine() { return m_renderingEngine; }

};

