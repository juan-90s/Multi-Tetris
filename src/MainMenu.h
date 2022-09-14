#pragma once
#include "MTSMenu.h"
#include "MTSLabel.h"

class MainMenu :
    public MTSMenu
{
public:
	using MTSMenu::MTSMenu;
	void init() override;
	void release() override;
private:
	void nav_right() override;
};

