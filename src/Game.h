#pragma once
#include "SDL.h"
#include "Tetris.h"

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
	int m_iWidth;
	int m_iHeight;
	SDL_Window* m_gWindow;
	SDL_Renderer* m_gRenderer;

	bool m_bUpdate;
	int m_iDelay;

	Tetris m_Tetris;
};

