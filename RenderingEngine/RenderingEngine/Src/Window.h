#pragma once

#include <SDL.h>
#include <string>
#include "Input\Input.h"

class Window
{

	int				m_width;
	int				m_height;
	std::string		m_title;
	SDL_Window*		m_window;
	SDL_GLContext	m_glContext;
	Input			m_input;
	bool			m_isCloseRequested;

public:

	Window(int width, int height, const std::string& title);
	virtual ~Window();

	void Update();
	void SwapBuffers();
	void BindAsRenderTarget() const;

	inline bool IsCloseRequested() const { return m_isCloseRequested; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline float GetAspect() const { return (float)m_width / (float)m_height; }
	inline const std::string& GetTitle() const { return m_title; }
	inline Vector2f GetCenter() const { return Vector2f((float)m_width / 2.0f, (float)m_height / 2.0f); }
	inline SDL_Window* GetSDLWindow() { return m_window; }
	inline const Input& GetInput() const { return m_input; }

	void SetFullScreen(bool value);
};

