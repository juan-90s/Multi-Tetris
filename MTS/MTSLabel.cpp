#include "MTSLabel.h"

MTSLabel::MTSLabel(std::string_view str_view, const MTSFont& font) :
	m_font(MTSFont(font)), 
	m_text(std::string(str_view)),
	m_texture(MTSTexture(m_font.getFont(), m_text.c_str(), m_font.getColor()))
{
	rect.w = m_texture.getWidth();
	rect.h = m_texture.getHeight();
}

// Label Specific 
void MTSLabel::render()
{
	SDL_Rect dstRect{ rect };
	dstRect.x += superX;
	dstRect.y += superY;

	switch (this->align)
	{
	case Align::LEFT:
		dstRect.y -= dstRect.h / 2;
		break;      
	case Align::CENTER:
		dstRect.x -= dstRect.w / 2;
		dstRect.y -= dstRect.h / 2;
		break;
	case Align::RIGHT:
		dstRect.x -= dstRect.w;
		dstRect.y -= dstRect.h / 2;
		break;
	default:
		dstRect.y -= dstRect.h / 2;
		break;
	}
	m_texture.render(dstRect);
	MTSView::render();
}

void MTSLabel::setText(std::string_view str_view)
{
	m_text = std::string(str_view);
	m_texture = MTSTexture(m_font.getFont(), m_text.c_str(), m_font.getColor());
	rect.w = m_texture.getWidth();
	rect.h = m_texture.getHeight();
}

std::string_view MTSLabel::getText() const
{
	return std::string_view(m_text);
}

MTSFont MTSLabel::getFont() const
{
	return m_font;
}
