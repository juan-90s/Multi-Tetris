#include "Tetris.h"


Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
	this->m_iRows = rows;
	this->m_iCols = cols;
	this->m_ilLeft = left;
	this->m_iTop = top;
	this->m_iBlockSize = blockSize;

	for (int i = 0; i < rows; i++) {
		std::vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		m_vec2dGrid.push_back(mapRow);
	}
	MTSFont novem("assets/novem___.ttf", 50, {200, 200, 200 });
	m_labelScore = MTSLabel("SCORE: ", novem);
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

void Tetris::clean()
{
	playerBlock.clean();
}

void Tetris::draw()
{
	// get blocks texture
	MTSTexture* m_IMGS = Block::getIMGs();
	
	
	// render player block
	playerBlock.pCur->draw(m_ilLeft, m_iTop, m_iBlockSize);
	playerBlock.pNext->draw(m_ilLeft + (m_iCols + 8) * m_iBlockSize, m_iTop, m_iBlockSize);

	SDL_Rect dstRect = {};
	dstRect.w = m_iBlockSize;
	dstRect.h = m_iBlockSize;
	// render frame
	for (int i = 0; i < m_iRows; i++) {
		// render line by line
		dstRect.y = m_iTop + i * m_iBlockSize;

		// render grey block wall in left
		dstRect.x = m_ilLeft - m_iBlockSize;
		m_IMGS[0].copyToRenderer(NULL, &dstRect);

		// render grey block wall in right
		dstRect.x = m_ilLeft + m_iCols * m_iBlockSize;
		m_IMGS[0].copyToRenderer(NULL, &dstRect);

		for (int j = 0; j < m_iCols; j++) {
			if (m_vec2dGrid[i][j] == 0) continue;
			dstRect.x = m_ilLeft + j * m_iBlockSize;
			m_IMGS[m_vec2dGrid[i][j]].copyToRenderer(NULL, &dstRect);
		}
	}

	// render bottom
	dstRect.y = m_iTop + m_iRows * m_iBlockSize;
	for (int j = -1; j < m_iCols + 1; j++) {
		dstRect.x = m_ilLeft + j * m_iBlockSize;
		m_IMGS[0].copyToRenderer(NULL, &dstRect);
	}

	// render label
	m_labelScore.setText("Score: " + std::to_string(m_iScore));
	m_labelScore.copyToRenderer(m_ilLeft + m_iCols * m_iBlockSize + 10, m_iTop + m_iRows * m_iBlockSize / 2, Align::LEFT);
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

void PlayerBlock::clean() 
{
	/*delete pNext;
	delete pCur;*/
	//pNext.release();
	//pCur.release();
}

inline void PlayerBlock::backup()
{
	pBak = *pCur;
}

void PlayerBlock::recover()
{
	*pCur = pBak;
}

void PlayerBlock::nextNew() {
	pCur = std::move(pNext);
	pNext = std::make_unique<Block>();
}

bool PlayerBlock::speedControl()
{
	pSpeedWindw = (pSpeedWindw + 1) % pSpeedMulti;
	return bool(pSpeedWindw);
}

void PlayerBlock::unlockControl()
{
	pSpeedWindw = -1;
}
