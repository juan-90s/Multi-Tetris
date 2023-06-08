#pragma once
#include "MTSMenu.h"
#include "MTSLabel.h"

class MainMenu :
    public MTSMenu
{
public:
	using MTSMenu::MTSMenu;
	void init() override;
private:
	void enter_select() override;
};

