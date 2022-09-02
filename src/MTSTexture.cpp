#include <iostream>
#include "MTSTexture.h"
#include "SDL.h"
#include "SDL_image.h"

struct sdl_deleter
{
	void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
	void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
	void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
};

SDL_Renderer* MTSTexture::s_renderer = 0;

MTSTexture::MTSTexture(const int width, const int height)
{
	m_width = width;
	m_height = height;
	SDL_Texture* texture_ptr = SDL_CreateTexture(s_renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		m_width, m_height);
	m_SDLtexture = std::shared_ptr<SDL_Texture>(texture_ptr, sdl_deleter());
}

MTSTexture::MTSTexture(const char* filename, const int width, const int height)
{
	SDL_ClearError();
	SDL_Texture* texture_ptr = IMG_LoadTexture(s_renderer, filename);
	if (texture_ptr) {
		SDL_QueryTexture(texture_ptr, NULL, NULL, &m_width, &m_height);
		bool needResize = bool(width && height) && (m_width != width) && (m_height != height);
		if (needResize)
		{
			m_width = width;
			m_height = height;
			const SDL_Rect dstRect = { 0, 0, m_width, m_height };

			SDL_Texture* resizedTexture = SDL_CreateTexture(s_renderer,
				SDL_PIXELFORMAT_RGBA8888,
				SDL_TEXTUREACCESS_TARGET,
				m_width, m_height);
			SDL_SetRenderTarget(s_renderer, resizedTexture);
			SDL_RenderCopy(s_renderer, texture_ptr, NULL, &dstRect);
			SDL_SetRenderTarget(s_renderer, NULL);

			SDL_DestroyTexture(texture_ptr);
			texture_ptr = resizedTexture;
		}
	}
	else {
		// couldn't load
		const char* errMessage = IMG_GetError();
		std::cerr << errMessage << std::endl;
		texture_ptr = SDL_CreateTexture(s_renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			m_width, m_height);
	}
	m_SDLtexture = std::shared_ptr<SDL_Texture>(texture_ptr, sdl_deleter());
}

void MTSTexture::setRenderer(SDL_Renderer* renderer)
{
	s_renderer = renderer;
}

void MTSTexture::copyToRenderer(const Rect* src, const Rect* dst)
{
	SDL_Rect* src_ptr;
	SDL_Rect* dst_ptr;
	if (src) {
		SDL_Rect srcRect = { src->x, src->y, src->w, src->h };
		src_ptr = &srcRect;
	}
	else
	{
		src_ptr = NULL;
	}
	if (dst) {
		SDL_Rect dstRect = { dst->x, dst->y, dst->w, dst->h };
		dst_ptr = &dstRect;
	}
	else
	{
		dst_ptr = NULL;
	}
	SDL_ClearError();
	int res = SDL_RenderCopy(s_renderer, m_SDLtexture.get(), src_ptr, dst_ptr);
	if (res < 0)
		const char* err = SDL_GetError();
	
}

void MTSTexture::copyToTexture(MTSTexture& otherTexture, const Rect* src, const Rect* dst)
{
	SDL_Rect* src_ptr;
	SDL_Rect* dst_ptr;
	if (src) {
		SDL_Rect srcRect = { src->x, src->y, src->w, src->h };
		src_ptr = &srcRect;
	}
	else
	{
		src_ptr = 0;
	}
	if (dst) {
		SDL_Rect dstRect = { dst->x, dst->y, dst->w, dst->h };
		dst_ptr = &dstRect;
	}
	else
	{
		dst_ptr = 0;
	}

	SDL_SetTextureBlendMode(otherTexture.m_SDLtexture.get(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(s_renderer, otherTexture.m_SDLtexture.get());
	SDL_RenderCopy(s_renderer, this->m_SDLtexture.get(), src_ptr, dst_ptr);
	SDL_SetRenderTarget(s_renderer, NULL);
}

bool MTSTexture::isEmpty() const
{
	if (!m_SDLtexture)
		return true;
	else
		return false;
}

int MTSTexture::getWidth() const
{
	return m_width;
}

int MTSTexture::getHeight() const
{
	return m_height;
}
