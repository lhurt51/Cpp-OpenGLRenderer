#include "CoreEngine.h"
#include "Utils\Util.h"
#include "Utils\Time\Time.h"
#include "Window.h"
#include "Input\Input.h"
#include "Game.h"


CoreEngine::CoreEngine(int width, int height, double frameRate, Game* game) :
	m_isRunning(false),
	m_width(width),
	m_height(height),
	m_frameTime(1.0/frameRate),
	m_game(game),
	m_renderingEngine(NULL)
{
	m_game->SetEngine(this);
}

CoreEngine::~CoreEngine()
{
	if (m_window) delete m_window;
	if (m_renderingEngine) delete m_renderingEngine;
}

void CoreEngine::CreateWindow(const std::string & title)
{
	m_window = new Window(m_width, m_height, title);
	m_renderingEngine = new RenderingEngine(*m_window);
}

void CoreEngine::Start()
{
	if (m_isRunning)
	{
		return;
	}

	Run();
}

void CoreEngine::Stop()
{
	if (!m_isRunning)
	{
		return;
	}

	m_isRunning = false;
}

void CoreEngine::Run()
{
	m_isRunning = true;

	m_game->Init(*m_window);

	double lastTime = Time::GetTime();
	double unprocessedTime = 0;
	double framesCounter = 0;
	int frames = 0;

	while (m_isRunning)
	{
		bool render = false;

		double startTime = Time::GetTime();
		double passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessedTime += passedTime;
		framesCounter += passedTime;

		if (framesCounter >= 1.0)
		{
			double totalTime = ((1000.0 * framesCounter) / (double)frames);
			double totalRecordedTime = 0.0;
			// printf("%i\n", frames);
			totalRecordedTime += m_game->DisplayInputTime((double)frames);
			totalRecordedTime += m_game->DisplayUpdateTime((double)frames);
			totalRecordedTime += m_renderingEngine->DisplayRenderTime((double)frames);
			totalRecordedTime += m_sleepTimer.DisplayAndReset("Sleep Timer: ", (double)frames);
			totalRecordedTime += m_windowUpdateTimer.DisplayAndReset("Window Update Time: ", (double)frames);
			totalRecordedTime += m_swapBufferTimer.DisplayAndReset("Buffer Swap Time: ", (double)frames);
			totalRecordedTime += m_renderingEngine->DisplayWindowSyncTime((double)frames);
			printf("Other Time:                             %f ms\n", totalTime - totalRecordedTime);
			printf("Total Time:                             %f ms\n", totalTime);
			frames = 0;
			framesCounter = 0;
		}

		while (unprocessedTime > m_frameTime)
		{
			m_windowUpdateTimer.StartInvocation();
			m_window->Update();

			if (m_window->IsCloseRequested())
			{
				Stop();
			}
			m_windowUpdateTimer.StopInvocation();

			m_game->ProcessInput(m_window->GetInput(), (float)m_frameTime);
			m_game->Update((float)m_frameTime);

			render = true;

			unprocessedTime -= m_frameTime;
		}

		if (render)
		{
			m_game->Render(m_renderingEngine, *m_mainCamera);
			m_swapBufferTimer.StartInvocation();
			m_window->SwapBuffers();
			m_swapBufferTimer.StopInvocation();
			frames++;
		}
		else
		{
			m_sleepTimer.StartInvocation();
			Util::Sleep(1);
			m_sleepTimer.StopInvocation();
		}
	}
}
