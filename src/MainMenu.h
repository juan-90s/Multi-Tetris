#pragma once
#include "MTSScene.h"
#include "MTSLabel.h"

class MainMenu :
    public MTSScene
{
public:
	MainMenu(const SDL_Rect& rect);
	void init() override;
	void release() override;
	void draw() override;
	void update() override;
	void handleEvent(SDL_Event& event) override;
private:
	void nav_up();
	void nav_down();
	void nav_in();
	
	int m_index = 0;
	MTSLabel m_arrLabel[3] = {};
	MTSLabel m_Cursor;
};

