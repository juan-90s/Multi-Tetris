#include "Tetris.h"


Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
	this->m_rows = rows;
	this->m_cols = cols;
	this->m_leftMargin = left;
	this->m_topMargin = top;
	this->m_blockSize = blockSize;

	for (int i = 0; i < rows; i++) {
		std::vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		m_grid.push_back(mapRow);
	}
}

void Tetris::init()
{
	// refresh blocks data
	for (int i = 0; i < m_grid.size(); i++) {
		for (int j = 0; j < m_grid[i].size(); j++) {
			m_grid[i][j] = 0;
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
	// render frame
	
	
	playerBlock.pCur->draw(m_leftMargin, m_topMargin, m_blockSize);
	playerBlock.pNext->draw(10, 50, m_blockSize);

	Rect dstrect = {};
	dstrect.w = m_blockSize;
	dstrect.h = m_blockSize;

	for (int i = 0; i < m_rows; i++) {
		// render line by line
		dstrect.y = m_topMargin + i * m_blockSize;

		// render grey block wall in left
		dstrect.x = m_leftMargin - m_blockSize;
		m_IMGS[0].copyToRenderer(NULL, &dstrect);

		// render grey block wall in right
		dstrect.x = m_leftMargin + m_cols * m_blockSize;
		m_IMGS[0].copyToRenderer(NULL, &dstrect);

		for (int j = 0; j < m_cols; j++) {
			if (m_grid[i][j] == 0) continue;
			dstrect.x = m_leftMargin + j * m_blockSize;
			m_IMGS[m_grid[i][j]].copyToRenderer(NULL, &dstrect);
		}
	}

	// render bottom
	dstrect.y = m_topMargin + m_rows * m_blockSize;
	for (int j = -1; j < m_cols + 1; j++) {
		dstrect.x = m_leftMargin + j * m_blockSize;
		m_IMGS[0].copyToRenderer(NULL, &dstrect);
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

void Tetris::clearLine()
{
	int lines = 0;
	int k = m_rows - 1;
	for (int i = m_rows - 1; i >= 0; i--) {
		// check whether row i is fully filled
		int count = 0;
		for (int j = 0; j < m_cols; j++) {
			if (m_grid[i][j]) {
				count++;
			}
			m_grid[k][j] = m_grid[i][j];
		}

		if (count < m_cols) {  
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
		if (points[i].row < 0 || points[i].row >= m_rows ||
			points[i].col < 0 || points[i].col >= m_cols ||
			m_grid[points[i].row][points[i].col] != 0)
			return false; 
	}
	return true;
}

void Tetris::fixBlock(Block* block)
{	
	Point* points = block->getPoints();
	for (int i = 0; i < 4; i++) {
		// mark type value on map
		m_grid[points[i].row][points[i].col] = block->getType();
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
