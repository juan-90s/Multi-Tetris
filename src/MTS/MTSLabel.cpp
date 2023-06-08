#include "MTSLabel.h"

MTSLabel::MTSLabel(std::string_view str_view, const MTSFont& font)
{
	m_font = MTSFont(font);
	m_text = std::string(str_view);
	SDL_Surface* t_surf_label = TTF_RenderText_Solid(m_font.getFont(), m_text.c_str(), m_font.getColor());
	SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(s_renderer, t_surf_label);
	SDL_FreeSurface(t_surf_label);
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

void MTSLabel::setText(std::string_view str_view)
{
	m_text = std::string(str_view);
	SDL_Surface* t_surf_label = TTF_RenderText_Solid(m_font.getFont(), m_text.c_str(), m_font.getColor());
	SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(s_renderer, t_surf_label);
	SDL_FreeSurface(t_surf_label);
	m_texture_ptr = std::shared_ptr<SDL_Texture>(texture_ptr, sdl_deleter());
}

std::string_view MTSLabel::getText() const
{
	return std::string_view(m_text);
}

MTSFont MTSLabel::getFont() const
{
	return m_font;
}
