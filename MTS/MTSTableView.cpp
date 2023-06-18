#include "MTSTableView.h"

void MTSTableView::render()
{
	for (int i = 0; i < m_cells.size(); i++) {
		auto view = m_cells[i].lock();
		view->setPos(view->getRect().x, i * m_rowHeight);
	}
	MTSView::render();
}

void MTSTableView::addCell(std::shared_ptr<MTSView> cell)
{
	m_cells.push_back(cell);
	addSubView(cell);
}

void MTSTableView::setRowHeight(int height)
{
	m_rowHeight = height;
}



std::shared_ptr<MTSView> MTSTableView::getCell(unsigned index) const
{
	if (index >= m_cells.size())
		return std::shared_ptr<MTSView>(nullptr);
	return m_cells.at(index).lock();
}



std::size_t MTSTableView::getCellNum() const
{
	return m_cells.size();
}
