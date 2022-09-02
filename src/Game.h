#pragma once
#include "SDL.h"
#include "Tetris.h"
#include "MTSTexture.h"

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
	int m_iWidth = 0;
	int m_iHeight = 0;
	SDL_Window* m_gWindow = 0;
	SDL_Renderer* m_gRenderer = 0;

	bool m_bUpdate;
	int m_iDelay;

	Tetris m_Tetris;
	MTSTexture bg;
};

