#include "MTSView.h"

void MTSView::render()
{
	for (auto& subView : m_SubViews) {
		subView->render();
	}
}

void MTSView::addSubView(std::shared_ptr<MTSView> subview)
{
	m_SubViews.push_back(subview);
	subview->superX = this->rect.x + this->superX;
	subview->superY = this->rect.y + this->superY;
	subview->syncSubRect();
}

const SDL_Rect& MTSView::getRect() const
{
	return this->rect;
}

void MTSView::setRect(const SDL_Rect& rect)
{
	this->rect = rect;
	syncSubRect();
}

void MTSView::setPos(const int x, const int y)
{
	this->rect.x = x;
	this->rect.y = y;
	syncSubRect();
}

void MTSView::syncSubRect()
{
	for (auto subview : m_SubViews) {
		subview->superX = this->rect.x + this->superX;
		subview->superY = this->rect.y + this->superY;
		subview->syncSubRect();
	}
}

