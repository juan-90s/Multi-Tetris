#pragma once
#include "SDL_rect.h"
#include "SDL_events.h"
#include "memory"

class MTSScene
{
public:
	virtual void init() {};
	virtual void quit() {};
	virtual void update() {};
	virtual void draw() {};
	virtual void handleEvent(SDL_Event& event ) {};

protected:
	void push(MTSScene* pScene);
	void jumpto(MTSScene* pScene);

	SDL_Rect m_Rect;
};

