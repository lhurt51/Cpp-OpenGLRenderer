#pragma once

#include <string>
#include "RenderingEngine.h"

class Game;

class CoreEngine
{

	ProfileTimer		m_sleepTimer;
	ProfileTimer		m_windowUpdateTimer;
	ProfileTimer		m_swapBufferTimer;

	bool				m_isRunning;
	int					m_width;
	int					m_height;
	double				m_frameTime;
	Game*				m_game;
	RenderingEngine*	m_renderingEngine;
	Window*				m_window;
	const Camera*		m_mainCamera;

public:

	CoreEngine(int width, int height, double frameRate, Game* game);
	virtual ~CoreEngine();

	void CreateWindow(const std::string& title);

	void Start();
	void Stop();

	inline RenderingEngine* GetRenderingEngine() { return m_renderingEngine; }
	void SetCamera(const Camera& camera) { m_mainCamera = &camera; }

private:

	void Run();

};

