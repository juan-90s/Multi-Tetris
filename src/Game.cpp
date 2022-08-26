#include "Game.h"
#include <time.h>
#include <stdlib.h>

const int SPEED_NORMAL = 100;  // ms

Game::Game()
{
	window_width = 960;
	window_height = 720;
	delay = SPEED_NORMAL;
	update = false;
	// initialize SDL window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		IMG_Init(IMG_INIT_PNG);
		// setup window size
		WINDOW = SDL_CreateWindow("Tetris",
			0,
			30,
			window_width, window_height,
			SDL_WINDOW_SHOWN);

		if (WINDOW != 0) {
			RENDERER = SDL_CreateRenderer(WINDOW, -1, 0);
			tetris = Tetris(RENDERER, 20, 10, 480, 50, 32);
		}
	}
	else {
		exit(1);
	}
	
}

void Game::play()
{
	// config random seed
	srand((unsigned int)time(0));
	tetris.init();

	int timer = 0;
	while (inputEvent()) {
		SDL_Delay(1);
		timer += getDelay();
		if (timer > delay) {
			timer = 0;
			tetris.drop(tetris.player(1));
			update = true;
		}

		if (update) {
			update = false;
			// update screen
			render();
			tetris.clearLine();
		}
	}

	quit();
}

void Game::render()
{
	SDL_RenderClear(RENDERER);
	//
	tetris.draw();

	SDL_RenderPresent(RENDERER);
}

void Game::quit()
{
	tetris.clean();
	SDL_DestroyRenderer(RENDERER);
	SDL_DestroyWindow(WINDOW);
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
				tetris.moveLeftRight(tetris.player(1), -1);
				update = true;
				break;
			case SDLK_RIGHT:
				tetris.moveLeftRight(tetris.player(1), 1);
				update = true;
				break;
			case SDLK_UP:
				tetris.rotate(tetris.player(1));
				update = true;
				break;
			case SDLK_DOWN:
				tetris.player(1).unlockControl();
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
int Game::getDelay()
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
