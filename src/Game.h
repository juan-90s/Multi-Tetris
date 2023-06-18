#pragma once
#include "SDL.h"
#include "MTSTexture.h"
#include <vector>

class Game
{
public:
	Game();
	void play();
private:
	void render();
	void quit();
	bool inputEvent();
	int getDelay() const;		// get last time calling this method

private:
	SDL_Window* m_gWindow = 0;
	SDL_Renderer* m_gRenderer = 0;

	int m_iDelay;

	MTSTexture bg;
};

