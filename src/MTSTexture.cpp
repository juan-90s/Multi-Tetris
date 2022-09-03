#include <iostream>
#include "MTSTexture.h"
#include "SDL.h"
#include "SDL_image.h"


void sdl_deleter::operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
void sdl_deleter::operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
void sdl_deleter::operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }

SDL_Renderer* MTSTexture::s_renderer = 0;

MTSTexture::MTSTexture(const int width, const int height)
{
	if (!checkRenderer()) return;
	SDL_Texture* texture_ptr = SDL_CreateTexture(s_renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width, height);
	m_texture_ptr = std::shared_ptr<SDL_Texture>(texture_ptr, sdl_deleter());
}

MTSTexture::MTSTexture(const char* filename, const int width, const int height)
{
	if (!checkRenderer()) return;
	SDL_Texture* texture_ptr = IMG_LoadTexture(s_renderer, filename);
	if (texture_ptr) {
		int t_width = 0;
		int t_height = 0;
		SDL_QueryTexture(texture_ptr, NULL, NULL, &t_width, &t_height);
		bool needResize = bool(width && height) && (t_width != width) && (t_height != height);
		if (needResize)
		{
			t_width = width;
			t_height = height;
			const SDL_Rect dstRect = { 0, 0, t_width, t_height };

			SDL_Texture* resizedTexture = SDL_CreateTexture(s_renderer,
				SDL_PIXELFORMAT_RGBA8888,
				SDL_TEXTUREACCESS_TARGET,
				t_width, t_height);
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
			width, height);
	}
	m_texture_ptr = std::shared_ptr<SDL_Texture>(texture_ptr, sdl_deleter());
}

void MTSTexture::setRenderer(SDL_Renderer* renderer)
{
	s_renderer = renderer;
}

bool MTSTexture::checkRenderer()
{
	return bool(s_renderer);
}

void MTSTexture::copyToRenderer(const SDL_Rect* src, const SDL_Rect* dst)
{
	if (!checkRenderer()) return;
	SDL_RenderCopy(s_renderer, m_texture_ptr.get(), src, dst);
	
}

void MTSTexture::copyToRenderer(const int x, const int y)
{
	if (!checkRenderer()) return;
	SDL_Rect dstRect = {};
	dstRect.x = x;
	dstRect.y = y;
	SDL_QueryTexture(m_texture_ptr.get(), NULL, NULL, &dstRect.w, &dstRect.h);
	SDL_RenderCopy(s_renderer, m_texture_ptr.get(), NULL, &dstRect);
}

void MTSTexture::copyToTexture(MTSTexture& otherTexture, const SDL_Rect* src, const SDL_Rect* dst)
{
	if (!checkRenderer()) return;

	SDL_SetTextureBlendMode(otherTexture.m_texture_ptr.get(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(s_renderer, otherTexture.m_texture_ptr.get());
	SDL_RenderCopy(s_renderer, this->m_texture_ptr.get(), src, dst);
	SDL_SetRenderTarget(s_renderer, NULL);
}

bool MTSTexture::isEmpty() const
{
	if (!m_texture_ptr)
		return true;
	else
		return false;
}

int MTSTexture::getWidth() const
{
	int t_width = 0;
	SDL_QueryTexture(m_texture_ptr.get(), NULL, NULL, &t_width, NULL);
	return t_width;
}

int MTSTexture::getHeight() const
{
	int t_height = 0;
	SDL_QueryTexture(m_texture_ptr.get(), NULL, NULL, NULL, &t_height);
	return t_height;
}
