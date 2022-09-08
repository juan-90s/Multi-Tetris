#pragma once
#include "SDL_rect.h"
#include "SDL_events.h"
#include "memory"

class MTSScene
{
public:
	MTSScene() = default;
	virtual void init() {};
	virtual void release() {};
	virtual void update() {};
	virtual void draw() {};
	virtual void handleEvent(SDL_Event& event ) {};
	void quit();

protected:
	void push(MTSScene* pScene);
	void jumpto(MTSScene* pScene);

	SDL_Rect m_Rect;
};

