#pragma once
#include <memory>
#include "SDL_rect.h"

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;

struct sdl_deleter
{
	void operator()(SDL_Window* p) const;
	void operator()(SDL_Renderer* p) const;
	void operator()(SDL_Texture* p) const;
};


class MTSTexture
{
public:
	MTSTexture() = default;
	MTSTexture(const MTSTexture&) = default;
	~MTSTexture() = default;
	MTSTexture& operator=(const MTSTexture& other) = default;
	MTSTexture& operator=(MTSTexture&& other) = default;


	MTSTexture(const int width, const int height);
	MTSTexture(const char* filename, const int width=0, const int height=0);
	
	static void setRenderer(SDL_Renderer* renderer);
	static bool checkRenderer();
	void copyToRenderer(const SDL_Rect* src, const SDL_Rect* dst);
	void copyToRenderer(const int x, const int y);
	void copyToTexture(MTSTexture& otherTexture, const SDL_Rect* src, const SDL_Rect* dst);

	bool isEmpty() const;
	int getWidth() const;
	int getHeight() const;

	
protected:
	static SDL_Renderer* s_renderer;
	std::shared_ptr<SDL_Texture> m_texture_ptr = nullptr;
};