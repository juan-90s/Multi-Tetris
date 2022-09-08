#include "MTSLabel.h"



MTSLabel::MTSLabel(const std::string str, const MTSFont& font)
{
	m_font = MTSFont(font);
	SDL_Surface* t_surf_label = TTF_RenderText_Solid(m_font.getFont(), str.c_str(), m_font.getColor());
	SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(s_renderer, t_surf_label);
	m_texture_ptr = std::shared_ptr<SDL_Texture>(texture_ptr, sdl_deleter());
}


// Label Specific 
void MTSLabel::copyToRenderer(const int x, const int y, const Align align_flag)
{
	if (!checkRenderer()) return;
	SDL_Rect dstRect = {};
	SDL_QueryTexture(m_texture_ptr.get(), NULL, NULL, &dstRect.w, &dstRect.h);
	switch (align_flag)
	{
	case Align::LEFT:
		dstRect.x = x;
		dstRect.y = y - dstRect.h / 2;
		break;      
	case Align::CENTER:
		dstRect.x = x - dstRect.w / 2;
		dstRect.y = y - dstRect.h / 2;
		break;
	case Align::RIGHT:
		dstRect.x = x - dstRect.w;
		dstRect.y = y - dstRect.h / 2;
		break;
	default:
		dstRect.x = x;
		dstRect.y = y - dstRect.h / 2;
		break;
	}
	SDL_RenderCopy(s_renderer, m_texture_ptr.get(), NULL, &dstRect);
}

void MTSLabel::setText(const std::string str)
{
	SDL_Surface* t_surf_label = TTF_RenderText_Solid(m_font.getFont(), str.c_str(), m_font.getColor());
	SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(s_renderer, t_surf_label);
	m_texture_ptr = std::shared_ptr<SDL_Texture>(texture_ptr, sdl_deleter());
}
