#pragma once
#include <memory>
// Rect: {x, y, w, h}
struct Rect {
	int x, y;
	int w, h;
};

struct SDL_Renderer;
struct SDL_Texture;

struct sdl_deleter;


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
	void copyToRenderer(const Rect* src, const Rect* dst);
	void copyToTexture(MTSTexture& otherTexture, const Rect* src, const Rect* dst);

	bool isEmpty() const;
	int getWidth() const;
	int getHeight() const;

	


private:
	static SDL_Renderer* s_renderer;
	//SDL_Texture* m_SDLtexture = nullptr;
	std::shared_ptr<SDL_Texture> m_SDLtexture = nullptr;
	int m_width = 0;
	int m_height = 0;
};