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
    void nav_in() override;
    Tetris* m_tetris;
};

