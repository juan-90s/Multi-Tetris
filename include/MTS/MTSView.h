#pragma once
#include <memory>
#include <vector>
#include "SDL_rect.h"

class MTSView
{
public:
	MTSView() = default;
	explicit MTSView(const SDL_Rect& rect) : rect(rect) {};
	virtual void init() {};
	virtual void render();

	void addSubView(std::shared_ptr<MTSView> subview);

	const SDL_Rect& getRect() const;
	virtual void setRect(const SDL_Rect& rect);
	void setPos(const int x, const int y);
	
protected:
	void syncSubRect();
	SDL_Rect rect = {};
	int superX{};
	int superY{};
private:
	std::vector<std::shared_ptr<MTSView>> m_SubViews{};
};

