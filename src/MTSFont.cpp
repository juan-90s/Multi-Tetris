#include "MTSFont.h"

void ttf_font_deleter(TTF_Font* p) { TTF_CloseFont(p); }

MTSFont::MTSFont(const char* fontPath, const int fontSize, const SDL_Color color)
{
	TTF_Font* t_font = TTF_OpenFont(fontPath, fontSize);
	m_font_ptr = std::shared_ptr<TTF_Font>(t_font, ttf_font_deleter);
	m_color = color;
}

SDL_Color MTSFont::getColor() const
{
	return m_color;
}

TTF_Font* MTSFont::getFont() const
{
	return m_font_ptr.get();
}
