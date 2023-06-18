#include <typeinfo>
#include "MTSMenu.h"
#include "MTSUtility.h"
#include "MTSTableView.h"
#include "MTSOptionView.h"

MTSMenu::MTSMenu()
{
	m_view = std::make_shared<MTSTableView>();
	m_tableView = std::dynamic_pointer_cast<MTSTableView>(m_view);
}

MTSMenu::MTSMenu(const SDL_Rect& rect)
{
	m_view = std::make_shared<MTSTableView>(rect);
	m_tableView = std::dynamic_pointer_cast<MTSTableView>(m_view);
}

void MTSMenu::renderCustom()
{
	//MTSTexture::fillRect(m_view->getRect(), {0,0,0,150});
}

void MTSMenu::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			nav_left();
			break;
		case SDLK_RIGHT:
			nav_right();
			break;
		case SDLK_UP:
			nav_up();
			break;
		case SDLK_DOWN:
			nav_down();
			break;
		case SDLK_RETURN:
			press_enter();
			break;
		case SDLK_ESCAPE:
			this->quit();
			break;
		}

		break;
	default:
		break;
	}
}

void MTSMenu::addCell(std::shared_ptr<MTSView> cell)
{
	auto tableview = std::dynamic_pointer_cast<MTSTableView>(m_view);
	tableview->addCell(cell);
}

void MTSMenu::nav_up()
{
	auto tableview = std::dynamic_pointer_cast<MTSTableView>(m_view);
	unsigned size = static_cast<unsigned>(tableview->getCellNum());
	inactivate(m_index);
	scroll(m_index, size, -1);
	activate(m_index);
}

void MTSMenu::nav_down()
{
	auto tableview = std::dynamic_pointer_cast<MTSTableView>(m_view);
	unsigned size = static_cast<unsigned>(tableview->getCellNum());
	inactivate(m_index);
	scroll(m_index, size, 1);
	activate(m_index);
}

void MTSMenu::nav_left()
{
	auto& celltype = typeid(*m_tableView->getCell(m_index));
	if (celltype.hash_code() == typeid(MTSOptionView).hash_code()) {
		auto optionview = std::dynamic_pointer_cast<MTSOptionView>(m_tableView->getCell(m_index));
		auto value = optionview->getValue();
		scroll(value, optionview->getOptionNum(), -1);
		optionview->setValue(value);
	}
}

void MTSMenu::nav_right()
{
	auto& celltype = typeid(*m_tableView->getCell(m_index));
	if (celltype.hash_code() == typeid(MTSOptionView).hash_code()) {
		auto optionview = std::dynamic_pointer_cast<MTSOptionView>(m_tableView->getCell(m_index));
		auto value = optionview->getValue();
		scroll(value, optionview->getOptionNum(), 1);
		optionview->setValue(value);
	}
}

void MTSMenu::activate(unsigned index)
{
	auto& celltype = typeid(*m_tableView->getCell(m_index));
	if (celltype.hash_code() == typeid(MTSOptionView).hash_code()) {
		auto optionview = std::dynamic_pointer_cast<MTSOptionView>(m_tableView->getCell(m_index));
		optionview->activate();
	}
	else if (celltype.hash_code() == typeid(MTSLabel).hash_code()) {
		auto label = std::dynamic_pointer_cast<MTSLabel>(m_tableView->getCell(m_index));
		label->setPos(80,0);
	}
}

void MTSMenu::inactivate(unsigned index)
{
	auto& celltype = typeid(*m_tableView->getCell(m_index));
	if (celltype.hash_code() == typeid(MTSOptionView).hash_code()) {
		auto optionview = std::dynamic_pointer_cast<MTSOptionView>(m_tableView->getCell(m_index));
		optionview->inactivate();
	}
	else if (celltype.hash_code() == typeid(MTSLabel).hash_code()) {
		auto label = std::dynamic_pointer_cast<MTSLabel>(m_tableView->getCell(m_index));
		label->setPos(0, 0);
	}
}


