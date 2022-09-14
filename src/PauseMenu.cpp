#include "PauseMenu.h"
#include "Tetris.h"

void PauseMenu::init()
{
	MTSFont font("assets/repetition.ttf", 50, { 255, 255, 255 });
	m_vecLabel.push_back(MTSLabel("RESUME", font));
	m_vecLabel.push_back(MTSLabel("OPTION", font));
	m_vecLabel.push_back(MTSLabel("QUIT", font));
}

void PauseMenu::setNestedGame(Tetris* game)
{
    m_tetris = game;
}

void PauseMenu::nav_right()
{
    switch (m_index)
    {
    case 0:
        m_tetris->setPause(false);
        break;

    case 1:

        break;

    case 2:
        m_tetris->quit();
        break;

    default:
        break;
    }
}


