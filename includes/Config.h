#pragma once
#include "SDL.h"
class Config
{
public:
	Config() = default;
	static void setWindow(SDL_Window* window);
	static void setMainWindowSize(int w, int h);
	static int getMainWindowWidth();
	static int getMainWindowHeight();
	
private:
	static SDL_Window* m_window;
	static int m_width;
	static int m_height;
};

