#pragma once
#include <memory>
#include "SDL_rect.h"
#include "SDL_events.h"
#include "MTSView.h"


class MTSScene
{
public:
	MTSScene() = default;
	explicit MTSScene(const SDL_Rect& rect) : m_view(std::make_shared<MTSView>(rect)) {};
	virtual void init() {};
	virtual void release() {};
	virtual void update() {};
	virtual void renderCustom() {};
	virtual void handleEvent(SDL_Event& event ) {};
	void quit();
	void addSubView(std::shared_ptr<MTSView> view_ptr);
	void render();

protected:
	void push(MTSScene* pScene);
	void jumpto(MTSScene* pScene);
	std::shared_ptr<MTSView> m_view;
};

