#pragma once
#include "MTSScene.h"
#include "MTSLabel.h"

class MainMenu :
    public MTSScene
{
public:
	void init() override;
	void quit() override;
	void draw() override;
	void update() override;
private:
	MTSLabel m_arrLabel[2];
};

