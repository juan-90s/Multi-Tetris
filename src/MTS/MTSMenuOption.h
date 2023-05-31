#pragma once
#include "MTSMenu.h"
class MTSMenuOption :
	public MTSMenu
{
public:
	using MTSMenu::MTSMenu;
	void draw() override;
protected:
	void nav_left() override;
	void nav_right() override;

	std::vector<MTSLabel> m_vecLabelRight;

	std::vector<std::vector<std::string>> m_vec2dOptions;
};