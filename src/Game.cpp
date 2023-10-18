#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Tetris.h"
#include "MainMenu.h"
#include "MTSSceneManager.h"
#include "Config.h"

namespace {
	const int FPS = 60;
	const int RENDER_DELAY = 1000 / FPS;
}

Game::Game()
{
	int width = 960;
	int height = 720;
	m_iDelay = RENDER_DELAY;

	// initialize SDL window and renderer
	bool isSDLinited = SDL_Init(SDL_INIT_EVERYTHING) >= 0;
	bool isIMGinited = (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG;
	bool isTTFinited = TTF_Init() >= 0;
	bool isMIXinited = Mix_OpenAudio(48000, AUDIO_S16, 2, 2048) >= 0;
	if (isSDLinited && isIMGinited && isTTFinited && isMIXinited) {
		// setup window size
		m_gWindow = SDL_CreateWindow("Tetris",
			0,
			30,
			width, height,
			SDL_WINDOW_SHOWN);

		if (m_gWindow != 0) {
			m_gRenderer = SDL_CreateRenderer(m_gWindow, -1, 0);
			MTSTexture::setRenderer(m_gRenderer);
			Config::setWindow(m_gWindow);
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
	SDL_Rect rect = {0, 0, Config::getMainWindowWidth(), Config::getMainWindowHeight() };
	MTSSceneManager::pushState(new MainMenu(rect));
	MTSSceneManager::getCurrent()->init();
	bg = MTSTexture("assets/background.png");
	int timer = 0;
	bool bUpdate = false;
	while (inputEvent()) {
		// empty scene stack guard
		if (MTSSceneManager::getCurrent() == nullptr) {
			break;
		}

		SDL_Delay(1);
		timer += getDelay();
		if (timer > m_iDelay) {
			timer = 0;
			bUpdate = true;
		}

		if (bUpdate) {
			bUpdate = false;
			MTSSceneManager::getCurrent()->update();
			render();
		}
	}

	quit();
}

void Game::render()
{
	SDL_RenderClear(m_gRenderer);
	bg.render(nullptr, nullptr);
	MTSSceneManager::getCurrent()->renderCustom();
	MTSSceneManager::getCurrent()->render();
	SDL_RenderPresent(m_gRenderer);
}

void Game::quit()
{
	SDL_DestroyRenderer(m_gRenderer);
	SDL_DestroyWindow(m_gWindow);
	IMG_Quit();
	Mix_Quit();
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