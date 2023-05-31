#pragma once
#include <memory>
#include "SDL_ttf.h"

class MTSFont
{
public:
	MTSFont() = default;
	~MTSFont() = default;
	MTSFont(const MTSFont&) = default;
	MTSFont& operator=(const MTSFont& other) = default;
	MTSFont& operator=(MTSFont&&) = default;

	MTSFont(const char* fontPath, const int fontSize, const SDL_Color color);
	SDL_Color getColor() const;
	TTF_Font* getFont() const;
private:
	std::shared_ptr<TTF_Font> m_font_ptr = nullptr;
	SDL_Color m_color = {};
};

