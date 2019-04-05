#pragma once

#include <SDL.h>
#include <string>

class Display
{

	bool m_isClosed;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

public:
	Display(int width, int height, const std::string& title);
	virtual ~Display(void);

	bool isClosed(void) const;

	void Update();
};

