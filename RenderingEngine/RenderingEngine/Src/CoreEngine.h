#pragma once

#include <string>
//#include "RenderingEngine.h"

//class Game;

class CoreEngine
{

	bool m_isRunning;
	int m_width;
	int m_height;
	double m_frameTime;
	// Game* m_game;
	// RenderingEngine* m_renderingEngine;

public:

	CoreEngine(int width, int height, double frameRate);
	// CoreEngine(int width, int height, double frameRate, Game* game);
	virtual ~CoreEngine();

	void CreateWindow(const std::string& title);

	void Start();
	void Stop();

	// inline RenderingEngine* GetRenderingEngine() { return m_renderingEngine; }

private:

	void Run();

};

