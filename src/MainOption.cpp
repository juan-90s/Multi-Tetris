#include "MainOption.h"
#include "MTSOptionView.h"
#include "Config.h"

void MainOption::init()
{
	MTSMenu::init();
	MTSFont font("assets/repetition.ttf", 40, { 255, 255, 255 });
	m_view->setRect({100, 100, Config::getMainWindowWidth() - 200, Config::getMainWindowHeight() - 200});
	std::vector<std::string> binary_options{"ON", "OFF"};
	std::vector<std::string> difficulty_options{"EASY", "NORMAL", "HARD"};

	auto musicoption = std::make_shared<MTSOptionView>("MUSIC", binary_options, font);
	musicoption->setRect({0,0,m_view->getRect().w,0});
	auto difftoption = std::make_shared<MTSOptionView>("DIFFICULTY", difficulty_options, font);
	difftoption->setRect({ 0,0,m_view->getRect().w,0});
	addCell(musicoption);
	addCell(difftoption);
	activate(0);
}
