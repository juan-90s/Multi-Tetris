#include "MTSMenu.h"

void MTSMenu::draw()
{
	MTSTexture::fillRect(m_Rect, {0,0,0,150});
	int x = (m_Rect.x + m_Rect.w) / 10;
	int y = 150;
	for (int i = 0; i < m_vecLabel.size(); i++) {
		if (i == m_index)
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
			nav_in();
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
	int size = (int)m_vecLabel.size();
	if (size) {
		int mod = (m_index - 1) % size;
		m_index = (mod < 0) ? mod + size : mod;
	}
}

void MTSMenu::nav_down()
{
	int size = (int)m_vecLabel.size();
	if (size) {
		int mod = (m_index + 1) % size;
		m_index = (mod < 0) ? mod + size : mod;
	}
		
}

void MTSMenu::nav_in()
{
	switch (m_index)
	{
	case 0:
		break;

	default:
		break;
	}
}
