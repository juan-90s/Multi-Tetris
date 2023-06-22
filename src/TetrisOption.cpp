#include "TetrisOption.h"
#include "Config.h"
#include "Tetris.h"

void TetrisOption::init()
{
	MTSFont font("assets/repetition.ttf", 40, { 255, 255, 255 });
    m_view->setRect({ 100, 100, Config::getMainWindowWidth() - 200, Config::getMainWindowHeight() - 200 });
	std::vector<std::string> playerNUM_options{"SINGLE","DOUBLE"};
	std::vector<std::string> gridSize_options{ "SMALL","MEDIUM","LARGE"};
    auto playnum_optionview{ std::make_shared<MTSOptionView>("PLAYER NUMBER", playerNUM_options, font) };
    playnum_optionview->setRect({ 0,0,m_view->getRect().w,0 });
    auto gridsize_optionview{ std::make_shared<MTSOptionView>("GRID SIZE", gridSize_options, font) };
    gridsize_optionview->setRect({ 0,0,m_view->getRect().w,0 });
    m_playnum_optionview = playnum_optionview;
    m_gridsize_optionview = gridsize_optionview;

	addCell(playnum_optionview);
	addCell(gridsize_optionview);
	addCell(std::make_shared<MTSLabel>("START GAME", font));
	activate(0);
}

void TetrisOption::press_enter()
{
    switch (m_index)
    {
    case 0:
        break;

    case 1:
        break;

    case 2:
        int playernum{ static_cast<int>(m_playnum_optionview.lock()->getValue()) + 1 };
        int gridsize{ static_cast<int>(m_gridsize_optionview.lock()->getValue())};
        int rows{18 + playernum * 2};
        int cols{5 + playernum * 5 + gridsize * 5};
        //int blocksize{ gridsize > 1 ? 16 : 32};
        jumpto(new Tetris({ 0, 0, Config::getMainWindowWidth(), Config::getMainWindowHeight() }, rows, cols, 32, playernum));
        break;
    }
}
