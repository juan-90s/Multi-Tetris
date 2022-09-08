#include "Tetris.h"
#include <sstream>
#include <iomanip>


Tetris::Tetris(const SDL_Rect& rect, const int rows, const int cols, const int blockSize)
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
	playerBlock = PlayerBlock();
}

void Tetris::draw()
{
	// get blocks texture
	MTSTexture* m_IMGS = Block::getIMGs();
	
	int margin_left = (m_Rect.x + m_Rect.w - m_iCols * m_iBlockSize) / 2;
	int margin_top = 10;
	
	// render player block
	playerBlock.pCur->draw(margin_left, margin_top, m_iBlockSize);
	playerBlock.pNext->draw(margin_left + (m_iCols + 4) * m_iBlockSize, margin_top, m_iBlockSize);

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
	drop(playerBlock);
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
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			moveLeftRight(playerBlock, -1);
			break;
		case SDLK_RIGHT:
			moveLeftRight(playerBlock, 1);
			break;
		case SDLK_UP:
			rotate(playerBlock);
			break;
		case SDLK_DOWN:
			playerBlock.unlockControl();
			break;
		case SDLK_ESCAPE:
			setPause(true);
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

	if (!checkBlock(pBlock.pCur.get())) {
		// touch botton or other blocks, fix
		fixBlock(&pBlock.pBak);
		pBlock.nextNew();
	}
}

void Tetris::moveLeftRight(PlayerBlock& pBlock, const int offset)
{
	pBlock.backup();
	pBlock.pCur->moveLeftRight(offset);

	if (!checkBlock(pBlock.pCur.get())) {
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

	if (!checkBlock(pBlock.pCur.get())) {
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
	return playerBlock;
}

bool Tetris::checkBlock(Block* block) const
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
