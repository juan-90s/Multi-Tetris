#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "SDL_image.h"

namespace {
	const int SPEED_NORMAL = 100;  // ms
}

Game::Game()
{
	m_iWidth = 960;
	m_iHeight = 720;
	m_iDelay = SPEED_NORMAL;
	m_bUpdate = false;
	// initialize SDL window and renderer
	bool isSDLinited = SDL_Init(SDL_INIT_EVERYTHING) >= 0;
	bool isIMGinited = (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG;
	if (isSDLinited && isIMGinited) {
		// setup window size
		m_gWindow = SDL_CreateWindow("Tetris",
			0,
			30,
			m_iWidth, m_iHeight,
			SDL_WINDOW_SHOWN);

		if (m_gWindow != 0) {
			m_gRenderer = SDL_CreateRenderer(m_gWindow, -1, 0);
			m_Tetris = Tetris(m_gRenderer, 20, 10, 480, 50, 32);
		}
	}
	else {
		std::cerr << "SDL initialization failed\n";
		std::cerr << SDL_GetError() << std::endl;
		exit(1);
	}
	
}

void Game::play()
{
	// config random seed
	srand((unsigned int)time(0));
	m_Tetris.init();

	int timer = 0;
	while (inputEvent()) {
		SDL_Delay(1);
		timer += getDelay();
		if (timer > m_iDelay) {
			timer = 0;
			m_Tetris.drop(m_Tetris.player(1));
			m_bUpdate = true;
		}

		if (m_bUpdate) {
			m_bUpdate = false;
			// update screen
			render();
			m_Tetris.clearLine();
		}
	}

	quit();
}

void Game::render()
{
	SDL_RenderClear(m_gRenderer);
	m_Tetris.draw();
	SDL_RenderPresent(m_gRenderer);
}

void Game::quit()
{
	m_Tetris.clean();
	SDL_DestroyRenderer(m_gRenderer);
	SDL_DestroyWindow(m_gWindow);
	SDL_Quit();
}

bool Game::inputEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_Tetris.moveLeftRight(m_Tetris.player(1), -1);
				m_bUpdate = true;
				break;
			case SDLK_RIGHT:
				m_Tetris.moveLeftRight(m_Tetris.player(1), 1);
				m_bUpdate = true;
				break;
			case SDLK_UP:
				m_Tetris.rotate(m_Tetris.player(1));
				m_bUpdate = true;
				break;
			case SDLK_DOWN:
				m_Tetris.player(1).unlockControl();
				break;
			}
			break;
		default:
			break;
		}
	}
	return true;
}

// first call: return 0
// return the time duration between this call and last call
int Game::getDelay() const
{
	static Uint32 lastTime = 0;
	Uint32 currentTime = SDL_GetTicks();
	if (lastTime == 0) {
		// first call
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = int(currentTime - lastTime);
		lastTime = currentTime;
		return ret;
	}
}
