#pragma once
#include "MTSMenu.h"
#include "MTSOptionView.h"

class TetrisOption:
	public MTSMenu
{
public:
	using MTSMenu::MTSMenu;
	void init() override;
private:
	std::weak_ptr<MTSOptionView> m_playnum_optionview;
	std::weak_ptr<MTSOptionView> m_gridsize_optionview;
	void press_enter() override;
};

