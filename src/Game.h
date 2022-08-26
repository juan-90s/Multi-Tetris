#pragma once
#include "Tetris.h"
#include "SDL.h"
class Game
{
public:
	Game();
	void play();
	void render();
	void quit();
private:
	bool inputEvent();
	int getDelay();		// get last time calling this method

private:
	int window_width, window_height;
	SDL_Window* WINDOW = NULL;
	SDL_Renderer* RENDERER = NULL;

	bool update;
	int delay;

	Tetris tetris = {0,0,0,0,0,0};


};

