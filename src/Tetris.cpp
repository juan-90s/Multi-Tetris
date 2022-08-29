#include "Tetris.h"
#include "SDL_image.h"



Tetris::Tetris(SDL_Renderer* m_renderer, int rows, int cols, int left, int top, int blockSize)
{
	this->m_renderer = m_renderer;
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
	/*-------------------- Texture Load -----------------------*/

	// draw frame (adaptive)
	SDL_Surface* surf = IMG_Load("assets/blocks.png");
	SDL_Rect srcrect = { 224, 0, surf->h, surf->h };  // pick the last block image
	SDL_Rect dstrest = { 0, 0, blockSize, blockSize };
	SDL_Texture* aio_img = SDL_CreateTextureFromSurface(m_renderer, surf);
	SDL_FreeSurface(surf);

	int frame_rows = rows + 1, frame_cols = cols + 2;
	m_frameIMG = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		frame_cols * blockSize, frame_rows * blockSize);
	SDL_SetTextureBlendMode(m_frameIMG, SDL_BLENDMODE_BLEND);  // avoid black ground
	SDL_SetRenderTarget(m_renderer, m_frameIMG);
	for (int i = 0; i < frame_rows; i++) {
		// draw in row
		dstrest.y = i * blockSize;
		if (i < frame_rows - 1) {
			// first block in this row
			dstrest.x = 0;
			SDL_RenderCopy(m_renderer, aio_img, &srcrect, &dstrest);
			// last block in this row
			dstrest.x = (frame_cols - 1) * blockSize;
			SDL_RenderCopy(m_renderer, aio_img, &srcrect, &dstrest);
		}
		else {
			// last row
			for (int j = 0; j < frame_cols; j++) {
				dstrest.x = j * blockSize;
				SDL_RenderCopy(m_renderer, aio_img, &srcrect, &dstrest);
			}
		}
	}
	SDL_DestroyTexture(aio_img);
	SDL_SetRenderTarget(m_renderer, NULL);
}

void Tetris::init()
{
	// refresh blocks data
	for (int i = 0; i < m_grid.size(); i++) {
		for (int j = 0; j < m_grid[i].size(); j++) {
			m_grid[i][j] = 0;
		}
	}

	//
	playerBlock = PlayerBlock(m_renderer);
}

void Tetris::clean()
{
	playerBlock.clean();
	SDL_DestroyTexture(m_frameIMG);
}

void Tetris::draw()
{
	// render frame
	SDL_Rect framerect = { m_leftMargin - m_blockSize, m_topMargin, };
	SDL_QueryTexture(m_frameIMG, NULL, NULL, &framerect.w, &framerect.h);
	SDL_RenderCopy(m_renderer, m_frameIMG, NULL, &framerect);
	
	playerBlock.pCur->draw(m_leftMargin, m_topMargin);
	playerBlock.pNext->draw(10, 50);

	SDL_Texture** m_IMGS = Block::getIMGs();
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (m_grid[i][j] == 0) continue;

			SDL_Rect dstrect = {0, };
			dstrect.x = j * m_blockSize + m_leftMargin;
			dstrect.y = i * m_blockSize + m_topMargin;
			dstrect.w = m_blockSize;
			dstrect.h = m_blockSize;
			SDL_RenderCopy(m_renderer, m_IMGS[m_grid[i][j] - 1], NULL, &dstrect);
		}
	}
}

void Tetris::drop(PlayerBlock &pBlock)
{
	// do not drop at current window 
	if (pBlock.speedControl()) return;

	pBlock.backup();
	pBlock.pCur->drop();

	if (!checkBlock(pBlock.pCur)) {
		// touch botton or other blocks, fix
		fixBlock(&pBlock.pBak);
		pBlock.nextNew(m_renderer);
	}
}

void Tetris::moveLeftRight(PlayerBlock& pBlock, const int offset)
{
	pBlock.backup();
	pBlock.pCur->moveLeftRight(offset);

	if (!checkBlock(pBlock.pCur)) {
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

	if (!checkBlock(pBlock.pCur)) {
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

PlayerBlock::PlayerBlock(SDL_Renderer* m_renderer) 
{
	pNext = new Block(m_renderer);
	pCur = pNext;
	pNext = new Block(m_renderer);
}

void PlayerBlock::clean() 
{
	delete pNext;
	delete pCur;
}

inline void PlayerBlock::backup()
{
	pBak = *pCur;
}

void PlayerBlock::recover()
{
	*pCur = pBak;
}

void PlayerBlock::nextNew(SDL_Renderer* m_renderer) {
	delete pCur;
	pCur = pNext;
	pNext = new Block(m_renderer);
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
