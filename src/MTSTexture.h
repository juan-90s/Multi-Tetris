#pragma once
#include "SDL.h"


class MTSTexture
{
public:
	MTSTexture() = default;
	MTSTexture(const int width, const int height);
	MTSTexture(const char* filename, const int width, const int height);
	~MTSTexture();
	static void setRenderer(SDL_Renderer* renderer);
	void copyToRenderer(const int left, const int top, const int width, const int height);
	void copyToTexture(MTSTexture& otherTexture, const int left, const int top, const int width, const int height);


private:
	static SDL_Renderer* s_renderer;
	SDL_Texture* m_SDLtexture;
	int m_width = 0;
	int m_height = 0;
};