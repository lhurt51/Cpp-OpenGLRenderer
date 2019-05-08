#include "CoreEngine.h"

#include "Utils/Util.h"
#include "Utils/Time/Time.h"
#include "../Rendering/Window/Window.h"
#include "Input/Input.h"
#include "Game/Game.h"


CoreEngine::CoreEngine(double frameRate, Window* window, RenderingEngine* renderingEngine, Game* game) :
	m_isRunning(false),
	m_frameTime(1.0/frameRate),
	m_window(window),
	m_renderingEngine(renderingEngine),
	m_game(game)
{
	m_game->SetEngine(this);
}

void CoreEngine::Start()
{
	if (m_isRunning)
	{
		return;
	}

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
			m_game->Render(m_renderingEngine);
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

void CoreEngine::Stop()
{
	m_isRunning = false;
}
