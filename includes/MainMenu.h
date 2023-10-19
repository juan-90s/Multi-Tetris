#pragma once
#include "MTSMenu.h"

class MainMenu :
    public MTSMenu
{
public:
	using MTSMenu::MTSMenu;
	void init() override;
private:
	void press_enter() override;
};

