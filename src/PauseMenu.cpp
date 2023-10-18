#include "PauseMenu.h"
#include "MainOption.h"
#include "MTSOptionView.h"
#include "Tetris.h"
#include "Config.h"

void PauseMenu::init()
{
    MTSMenu::init();
	MTSFont font("assets/repetition.ttf", 50, { 255, 255, 255 });
    m_view->setPos(100, 100);
    addCell(std::make_shared<MTSLabel>("RESUME", font));
    addCell(std::make_shared<MTSLabel>("OPTION", font));
    addCell(std::make_shared<MTSLabel>("QUIT", font));
    activate(0);
}

void PauseMenu::setNestedGame(Tetris* game)
{
    m_tetris = game;
}

void PauseMenu::press_enter()
{
    switch (m_index)
    {
    case 0:
        m_tetris->setPause(false);
        break;

    case 1:
        push(new MainOption(m_view->getRect()));
        break;

    case 2:
        m_tetris->quit();
        break;

    default:
        break;
    }
}


