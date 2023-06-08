#include "MTSMenu.h"
#include "MTSUtility.h"

void MTSMenu::draw()
{
	MTSTexture::fillRect(m_Rect, {0,0,0,150});
	int x = (m_Rect.x + m_Rect.w) / 10;
	int y = 150;
	for (int i = 0; i < m_vecLabel.size(); i++) {
		if (i == m_index)
			// current active label
			m_vecLabel[i].copyToRenderer(x + 20, y, Align::LEFT);
		else
			m_vecLabel[i].copyToRenderer(x, y, Align::LEFT);
		y += 80;
	}
}

void MTSMenu::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			enter_select();
			break;
		case SDLK_UP:
			nav_up();
			break;
		case SDLK_DOWN:
			nav_down();
			break;
		}
		break;
	default:
		break;
	}
}

void MTSMenu::nav_up()
{
	unsigned size = static_cast<unsigned>(m_vecLabel.size());
	scroll(m_index, size, -1);
}

void MTSMenu::nav_down()
{
	unsigned size = static_cast<unsigned>(m_vecLabel.size());
	scroll(m_index, size, 1);
}
