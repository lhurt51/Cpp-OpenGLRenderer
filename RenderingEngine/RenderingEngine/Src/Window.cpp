#include "Window.h"
#include <SDL.h>
#include <GL/glew.h>

Window::Window(int width, int height, const std::string & title) : m_width(width), m_height(height), m_title(title), m_input(this), m_isCloseRequested(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// MSAA 
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	SDL_GL_SetSwapInterval(1);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	}
}

Window::~Window()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void Window::Update()
{
	for (int i = 0; i < Input::NUM_MOUSEBUTTONS; i++)
	{
		m_input.SetMouseDown(i, false);
		m_input.SetMouseUp(i, false);
	}

	for (int i = 0; i < Input::NUM_KEYS; i++)
	{
		m_input.SetKeyDown(i, false);
		m_input.SetKeyUp(i, false);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_isCloseRequested = true;
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			m_input.SetMouseX(e.motion.x);
			m_input.SetMouseY(e.motion.y);
		}

		if (e.type == SDL_KEYDOWN)
		{
			int value = e.key.keysym.scancode;

			m_input.SetKey(value, true);
			m_input.SetKeyDown(value, true);
		}

		if (e.type == SDL_KEYUP)
		{
			int value = e.key.keysym.scancode;

			m_input.SetKey(value, false);
			m_input.SetKeyUp(value, true);
		}

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int value = e.button.button;

			m_input.SetMouse(value, true);
			m_input.SetMouseDown(value, true);
		}

		if (e.type == SDL_MOUSEBUTTONUP)
		{
			int value = e.button.button;

			m_input.SetMouse(value, false);
			m_input.SetMouseUp(value, true);
		}
	}
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

void Window::BindAsRenderTarget() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, GetWidth(), GetHeight());
}

void Window::SetFullScreen(bool value)
{
	int mode = 0;
	if (value)
	{
		mode = SDL_WINDOW_FULLSCREEN;
	}
	else
	{
		mode = 0;
	}

	SDL_SetWindowFullscreen(m_window, mode);
}
