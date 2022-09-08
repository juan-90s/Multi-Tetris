#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "SDL_image.h"
#include "Tetris.h"
#include "MainMenu.h"
#include "MTSSceneManager.h"



namespace {
	const int FPS = 60;
	const int RENDER_DELAY = 1000 / FPS;
}

Game::Game()
{
	m_iWidth = 960;
	m_iHeight = 720;
	m_iDelay = RENDER_DELAY;
	m_bUpdate = false;
	// initialize SDL window and renderer
	bool isSDLinited = SDL_Init(SDL_INIT_EVERYTHING) >= 0;
	bool isIMGinited = (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG;
	bool isTTFinited = TTF_Init() >= 0;
	if (isSDLinited && isIMGinited && isTTFinited) {
		// setup window size
		m_gWindow = SDL_CreateWindow("Tetris",
			0,
			30,
			m_iWidth, m_iHeight,
			SDL_WINDOW_SHOWN);

		if (m_gWindow != 0) {
			m_gRenderer = SDL_CreateRenderer(m_gWindow, -1, 0);
			MTSTexture::setRenderer(m_gRenderer);
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
	SDL_Rect rect = {0, 0, m_iWidth, m_iHeight};
	MTSSceneManager::pushState(new MainMenu(rect));
	MTSSceneManager::getCurrent()->init();
	bg = MTSTexture("assets/background.png");
	int timer = 0;
	while (inputEvent()) {
		if (MTSSceneManager::getCurrent() == nullptr)
			break;
		SDL_Delay(1);
		timer += getDelay();
		if (timer > m_iDelay) {
			timer = 0;
			m_bUpdate = true;
		}

		if (m_bUpdate) {
			m_bUpdate = false;
			MTSSceneManager::getCurrent()->update();
			render();
		}
	}

	quit();
}

void Game::render()
{
	SDL_RenderClear(m_gRenderer);
	bg.copyToRenderer(nullptr, nullptr);
	MTSSceneManager::getCurrent()->draw();
	SDL_RenderPresent(m_gRenderer);
}

void Game::quit()
{
	SDL_DestroyRenderer(m_gRenderer);
	SDL_DestroyWindow(m_gWindow);
	SDL_Quit();
}

bool Game::inputEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		MTSSceneManager::getCurrent()->handleEvent(event);
		switch (event.type)
		{
		case SDL_QUIT:
			return false;
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
