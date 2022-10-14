#include "Tetris.h"
#include <sstream>
#include <iomanip>


Tetris::Tetris(const SDL_Rect& rect, const int rows, const int cols, const int blockSize, const unsigned int playerNum)
{
	this->m_Rect = SDL_Rect(rect);
	this->m_iRows = rows;
	this->m_iCols = cols;
	this->m_iBlockSize = blockSize;

	for (int i = 0; i < rows; i++) {
		std::vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		m_vec2dGrid.push_back(mapRow);
	}

	if (playerNum > 1) {
		for (int i = 0; i < playerNum; i++) {
			int anchor = ((i + 1) * m_iCols / (playerNum + 1));
			BlockColor color = static_cast<BlockColor>(i+1);
			m_vecPlayers.push_back(PlayerBlock(color, anchor));
		}
	}
	else {
		m_vecPlayers.push_back(PlayerBlock());
	}

	

	MTSFont font("assets/repetition.ttf", 50, {255, 255, 255 });
	m_labelScore = MTSLabel("SCORE", font);
	m_labelScoreValue = MTSLabel("00000", font);
	m_PauseMenu = std::make_unique<PauseMenu>(rect);
	m_PauseMenu->init();
	m_PauseMenu->setNestedGame(this);
}

void Tetris::init()
{
	// refresh blocks data
	for (int i = 0; i < m_vec2dGrid.size(); i++) {
		for (int j = 0; j < m_vec2dGrid[i].size(); j++) {
			m_vec2dGrid[i][j] = 0;
		}
	}
	//playerBlock = PlayerBlock();
}

void Tetris::draw()
{
	// get blocks texture
	MTSTexture* m_IMGS = Block::getIMGs();
	
	int margin_left = (m_Rect.x + m_Rect.w - m_iCols * m_iBlockSize) / 2;
	int margin_top = 10;
	
	// render player block
	for (auto i = 0; i < m_vecPlayers.size(); i++) {
		m_vecPlayers[i].pCur->draw(margin_left, margin_top, m_iBlockSize);
		m_vecPlayers[i].pNext->draw(margin_left + (m_iCols + 4) * m_iBlockSize, margin_top + 5 * i * m_iBlockSize, m_iBlockSize);
	}

	//playerBlock.pCur->draw(margin_left, margin_top, m_iBlockSize);
	//playerBlock.pNext->draw(margin_left + (m_iCols + 4) * m_iBlockSize, margin_top, m_iBlockSize);

	SDL_Rect dstRect = {};
	dstRect.w = m_iBlockSize;
	dstRect.h = m_iBlockSize;
	// render frame
	for (int i = 0; i < m_iRows; i++) {
		// render line by line
		dstRect.y = margin_top + i * m_iBlockSize;

		// render grey block wall in left
		dstRect.x = margin_left - m_iBlockSize;
		m_IMGS[0].copyToRenderer(NULL, &dstRect);

		// render grey block wall in right
		dstRect.x = margin_left + m_iCols * m_iBlockSize;
		m_IMGS[0].copyToRenderer(NULL, &dstRect);

		for (int j = 0; j < m_iCols; j++) {
			if (m_vec2dGrid[i][j] == 0) continue;
			dstRect.x = margin_left + j * m_iBlockSize;
			m_IMGS[m_vec2dGrid[i][j]].copyToRenderer(NULL, &dstRect);
		}
	}

	// render bottom
	dstRect.y = margin_top + m_iRows * m_iBlockSize;
	for (int j = -1; j < m_iCols + 1; j++) {
		dstRect.x = margin_left + j * m_iBlockSize;
		m_IMGS[0].copyToRenderer(NULL, &dstRect);
	}

	// render label
	std::ostringstream ss;
	ss << std::setw(5) << std::setfill('0') << m_iScore;
	m_labelScoreValue.setText(ss.str());
	m_labelScore.copyToRenderer(margin_left + (m_iCols + 2) * m_iBlockSize,
								margin_top + m_iRows * m_iBlockSize / 2,
								Align::LEFT);
	m_labelScoreValue.copyToRenderer(margin_left + (m_iCols + 2) * m_iBlockSize,
									margin_top + m_iRows * m_iBlockSize / 2 + 50,
									Align::LEFT);

	if (m_bPause) {
		m_PauseMenu->draw();
	}
}

void Tetris::update()
{
	if (m_bPause)
		return;
	for (auto& player : m_vecPlayers) {
		drop(player);
	}
	clearLine();
	for (int value : m_vec2dGrid[1]) {
		if (value) {
			m_bPause = true;
			quit();
			return;
		}
	}
	
}

void Tetris::handleEvent(SDL_Event& event)
{
	if (m_bPause) {
		m_PauseMenu->handleEvent(event);
		return;
	}
	int playerNum = m_vecPlayers.size();
	auto& player1 = m_vecPlayers[0];
	auto& player2 = playerNum >= 2 ? m_vecPlayers[1] : m_vecPlayers[0];

	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			moveLeftRight(player1, -1);
			break;
		case SDLK_RIGHT:
			moveLeftRight(player1, 1);
			break;
		case SDLK_UP:
			rotate(player1);
			break;
		case SDLK_DOWN:
			player1.unlockControl();
			break;
		case SDLK_ESCAPE:
			setPause(true);
			break;

		case SDLK_a:
			moveLeftRight(player2, -1);
			break;
		case SDLK_d:
			moveLeftRight(player2, 1);
			break;
		case SDLK_w:
			rotate(player2);
			break;
		case SDLK_s:
			player2.unlockControl();
			break;
		}
		break;
	default:
		break;
	}
}

void Tetris::drop(PlayerBlock &pBlock)
{
	// do not drop at current window 
	if (pBlock.speedControl()) return;

	pBlock.backup();
	pBlock.pCur->drop();

	if (!checkInPlayers(pBlock.pCur.get())) {
		// cannot move to destination, recover
		pBlock.recover();
	}

	if (!checkInMap(pBlock.pCur.get())) {
		// touch botton or other blocks, fix
		fixBlock(&pBlock.pBak);
		pBlock.nextNew();
	}
}

void Tetris::moveLeftRight(PlayerBlock& pBlock, const int offset)
{
	pBlock.backup();
	pBlock.pCur->moveLeftRight(offset);

	if (!checkInMap(pBlock.pCur.get()) || !checkInPlayers(pBlock.pCur.get())) {
		// cannot move to destination, recover
		pBlock.recover();
	}
}

void Tetris::rotate(PlayerBlock& pBlock)
{
	// TODO: optimize rotate logic
	if (pBlock.pCur->getType() == 7)
		// if block is square, then do nothing
		return;
	pBlock.backup();
	pBlock.pCur->rotate();

	if (!checkInMap(pBlock.pCur.get()) || !checkInPlayers(pBlock.pCur.get())) {
		// cannot move to destination, recover
		pBlock.recover();
	}
}

void Tetris::setPause(bool bFlag)
{
	m_bPause = bFlag;
}

void Tetris::clearLine()
{
	int lines = 0;
	int k = m_iRows - 1;
	for (int i = m_iRows - 1; i >= 0; i--) {
		// check whether row i is fully filled
		int count = 0;
		for (int j = 0; j < m_iCols; j++) {
			if (m_vec2dGrid[i][j]) {
				count++;
			}
			m_vec2dGrid[k][j] = m_vec2dGrid[i][j];
		}

		if (count < m_iCols) {  
			// not fully filled, index k decrease as i
			k--;
		}
		else {
			lines++;
		}
	}

	if (lines > 0) {
		// TODO: calculate score
		// TODO: play SFX
		m_iScore += 10 * lines;
	}
}

PlayerBlock& Tetris::player(const int num)
{
	//return playerBlock;
	if (num < m_vecPlayers.size())
		return m_vecPlayers[num];
	else
		return m_vecPlayers[0];
}

bool Tetris::checkInMap(Block* block) const
{
	Point* points = block->getPoints();
	for (int i = 0; i < 4; i++) {
		if (points[i].row < 0 || points[i].row >= m_iRows ||
			points[i].col < 0 || points[i].col >= m_iCols ||
			m_vec2dGrid[points[i].row][points[i].col] != 0)
			return false; 
	}

	return true;
}

bool Tetris::checkInPlayers(Block* block) const 
{
	if (m_vecPlayers.size() == 1)
		return true;
	Point* points = block->getPoints();
	for (auto& player : m_vecPlayers) {
		if (block == player.pCur.get()) {
			continue;
		}
		Point* points2 = player.pCur->getPoints();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (points[i].col == points2[j].col && points[i].row == points2[j].row)
					return false;
			}
		}

	}
	return true;
}

void Tetris::fixBlock(Block* block)
{	
	Point* points = block->getPoints();
	for (int i = 0; i < 4; i++) {
		// mark type value on map
		m_vec2dGrid[points[i].row][points[i].col] = block->getType();
	}
}

PlayerBlock::PlayerBlock() 
{
	pNext = std::make_unique<Block>();
	pCur = std::move(pNext);
	pNext = std::make_unique<Block>();
}

PlayerBlock::PlayerBlock(const BlockColor color, const int x)
{
	anchorX = x;
	pColor = color;

	pNext = std::make_unique<Block>();
	pCur = std::move(pNext);
	pNext = std::make_unique<Block>();

	pCur->moveLeftRight(anchorX);
	if (pColor != BlockColor::NoColor) {
		pCur->setColor(pColor);
	}
}

inline void PlayerBlock::backup()
{
	pBak = *pCur;
}

void PlayerBlock::recover()
{
	*pCur = pBak;
}

void PlayerBlock::nextNew() 
{
	pCur = std::move(pNext);
	pNext = std::make_unique<Block>();

	pCur->moveLeftRight(anchorX);
	if (pColor != BlockColor::NoColor) {
		pCur->setColor(pColor);
	}
}

bool PlayerBlock::speedControl()
{
	pDelayWindw = (pDelayWindw + 1) % pDelayMulti;
	return bool(pDelayWindw);
}

void PlayerBlock::unlockControl()
{
	pDelayWindw = -1;
}
