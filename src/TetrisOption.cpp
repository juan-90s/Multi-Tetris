#include "TetrisOption.h"
#include "MTSOptionView.h"

void TetrisOption::init()
{
	MTSFont font("assets/repetition.ttf", 40, { 255, 255, 255 });
	std::vector<std::string> playerNUM_options{"Single","Double"};
	std::vector<std::string> gridSize_options{ "Small","Medium","Large"};
	m_tableView->addCell(std::make_shared<MTSOptionView>("Player Number", playerNUM_options, font));
	m_tableView->addCell(std::make_shared<MTSOptionView>("Grid Size", gridSize_options, font));
	activate(0);
}
