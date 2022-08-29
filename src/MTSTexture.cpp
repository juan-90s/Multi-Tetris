#include <iostream>
#include "MTSTexture.h"
#include "SDL_image.h"

SDL_Renderer* s_renderer = 0;

MTSTexture::MTSTexture()
{
	m_SDLtexture = SDL_CreateTexture(s_renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		m_width, m_height);
}

MTSTexture::MTSTexture(const int width, const int height)
{
	m_width = width;
	m_height = height;
	m_SDLtexture = SDL_CreateTexture(s_renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		m_width, m_height);
}

MTSTexture::MTSTexture(const char* filename, const int width=0, const int height=0)
{
	m_SDLtexture = IMG_LoadTexture(s_renderer, filename);
	if (!m_SDLtexture) {
		// couldn't load
		std::cerr << IMG_GetError() << std::endl;
		m_SDLtexture = SDL_CreateTexture(s_renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			m_width, m_height);
		return;
	}
	else {
		SDL_QueryTexture(m_SDLtexture, NULL, NULL, &m_width, &m_height);
	}
	bool needResize = bool(width && height) && (m_width != width) && (m_height != height);
	if (needResize)
	{
		m_width = width;
		m_height = height;
		const SDL_Rect dstRect = {0, 0, m_width, m_height};

		SDL_Texture* resizedTexture = SDL_CreateTexture(s_renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			m_width, m_height);
		SDL_SetRenderTarget(s_renderer, resizedTexture);
		SDL_RenderCopy(s_renderer, this->m_SDLtexture, NULL, &dstRect);
		SDL_SetRenderTarget(s_renderer, NULL);

		SDL_DestroyTexture(m_SDLtexture);
		m_SDLtexture = resizedTexture;
	}
	
}

MTSTexture::~MTSTexture()
{
	SDL_DestroyTexture(m_SDLtexture);
}

void MTSTexture::setRenderer(SDL_Renderer* renderer)
{
	s_renderer = renderer;
}

void MTSTexture::copyToRenderer(const int left, const int top, const int width, const int height)
{
	const SDL_Rect dstRect = {left, top, width, height};
	SDL_RenderCopy(s_renderer, m_SDLtexture, NULL, &dstRect);
}

void MTSTexture::copyToTexture(MTSTexture& otherTexture, const int left, const int top, const int width, const int height)
{
	const SDL_Rect dstRect = { left, top, width, height };
	SDL_SetRenderTarget(s_renderer, otherTexture.m_SDLtexture);
	SDL_RenderCopy(s_renderer, this->m_SDLtexture, NULL, &dstRect);
	SDL_SetRenderTarget(s_renderer, NULL);
}
