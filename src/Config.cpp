#include "Config.h"
int Config::m_height = 0;
int Config::m_width = 0;
SDL_Window* Config::m_window = nullptr;

void Config::setWindow(SDL_Window* window)
{
	m_window = window;
	SDL_GetWindowSize(m_window, &m_width, &m_height);
}

void Config::setMainWindowSize(int w, int h)
{
	m_width = w;
	m_height = h;
	if (m_window)
		return;

}

int Config::getMainWindowWidth()
{
	return m_width;
}

int Config::getMainWindowHeight()
{
	return m_height;
}
