#pragma once
#include "MTSMenu.h"
#include "MTSLabel.h"
#include <vector>

class Tetris;

class PauseMenu :
    public MTSMenu
{
public:
    using MTSMenu::MTSMenu;
    void init() override;
    void setNestedGame(Tetris* game);
private:
    void press_enter() override;
    Tetris* m_tetris;
};

