#pragma once
#include "SDL_rect.h"
#include "SDL_events.h"
#include "memory"

class MTSScene
{
public:
	MTSScene() = default;
	explicit MTSScene(const SDL_Rect& rect) : m_Rect(rect) {};
	virtual void init() {};
	virtual void release() {};
	virtual void update() {};
	virtual void draw() {};
	virtual void handleEvent(SDL_Event& event ) {};
	void quit();

protected:
	void push(MTSScene* pScene);
	void jumpto(MTSScene* pScene);

	SDL_Rect m_Rect = {};
};

