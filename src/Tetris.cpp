#include "Tetris.h"




Tetris::Tetris(SDL_Renderer* RENDERER, int rows, int cols, int left, int top, int blockSize)
{
	this->RENDERER = RENDERER;
	this->rows = rows;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;

	for (int i = 0; i < rows; i++) {
		std::vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Tetris::init()
{
	// refresh blocks data
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			map[i][j] = 0;
		}
	}

	//
	playerBlock = PlayerBlock(RENDERER);

	/*-------------------- Texture Load -----------------------*/
	// load background
	backgroundIMG = IMG_LoadTexture(RENDERER, "assets/background.png");

	// draw frame (adaptive)
	SDL_Surface* surf = IMG_Load("assets/blocks.png");
	SDL_Rect srcrect = {224, 0, surf->h, surf->h};  // pick the last block image
	SDL_Rect dstrest = {0, 0, blockSize, blockSize };
	SDL_Texture* aio_img = SDL_CreateTextureFromSurface(RENDERER, surf);
	SDL_FreeSurface(surf);

	int frame_rows = rows + 1, frame_cols = cols + 2;
	frameIMG = SDL_CreateTexture(RENDERER, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		frame_cols * blockSize, frame_rows * blockSize);
	SDL_SetTextureBlendMode(frameIMG, SDL_BLENDMODE_BLEND);  // avoid black ground
	SDL_SetRenderTarget(RENDERER, frameIMG);
	for (int i = 0; i < frame_rows; i++) {
		// draw in row
		dstrest.y = i * blockSize;
		if (i < frame_rows - 1) {
			// first block in this row
			dstrest.x = 0;
			SDL_RenderCopy(RENDERER, aio_img, &srcrect, &dstrest);
			// last block in this row
			dstrest.x = (frame_cols - 1) * blockSize;
			SDL_RenderCopy(RENDERER, aio_img, &srcrect, &dstrest);
		}
		else {
			// last row
			for (int j = 0; j < frame_cols; j++) {
				dstrest.x = j * blockSize;
				SDL_RenderCopy(RENDERER, aio_img, &srcrect, &dstrest);
			}
		}
	}
	SDL_DestroyTexture(aio_img);
	SDL_SetRenderTarget(RENDERER, NULL);
}

void Tetris::clean()
{
	playerBlock.clean();
	SDL_DestroyTexture(backgroundIMG);
	SDL_DestroyTexture(frameIMG);
}

void Tetris::draw()
{
	// render background
	SDL_RenderCopy(RENDERER, backgroundIMG, NULL, NULL);
	// render frame
	SDL_Rect framerect = { leftMargin - blockSize, topMargin, };
	SDL_QueryTexture(frameIMG, NULL, NULL, &framerect.w, &framerect.h);
	SDL_RenderCopy(RENDERER, frameIMG, NULL, &framerect);
	
	playerBlock.pCur->draw(leftMargin, topMargin);
	playerBlock.pNext->draw(10, 50);

	SDL_Texture** imgs = Block::getIMGs();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0) continue;

			SDL_Rect dstrect = {0, };
			dstrect.x = j * blockSize + leftMargin;
			dstrect.y = i * blockSize + topMargin;
			dstrect.w = blockSize;
			dstrect.h = blockSize;
			SDL_RenderCopy(RENDERER, imgs[map[i][j] - 1], NULL, &dstrect);
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
		pBlock.nextNew(RENDERER);
	}
}

void Tetris::moveLeftRight(PlayerBlock& pBlock, int offset)
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
	int k = rows - 1;
	for (int i = rows - 1; i >= 0; i--) {
		// check whether row i is fully filled
		int count = 0;
		for (int j = 0; j < cols; j++) {
			if (map[i][j]) {
				count++;
			}
			map[k][j] = map[i][j];
		}

		if (count < cols) {  
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

PlayerBlock& Tetris::player(int num)
{
	return playerBlock;
}

bool Tetris::checkBlock(Block* block)
{
	Point* points = block->getPoints();
	for (int i = 0; i < 4; i++) {
		if (points[i].row < 0 || points[i].row >= rows ||
			points[i].col < 0 || points[i].col >= cols ||
			map[points[i].row][points[i].col] != 0)
			return false; 
	}
	return true;
}

void Tetris::fixBlock(Block* block)
{	
	Point* points = block->getPoints();
	for (int i = 0; i < 4; i++) {
		// mark type value on map
		map[points[i].row][points[i].col] = block->getType();
	}
}

PlayerBlock::PlayerBlock(SDL_Renderer* RENDERER) 
{
	pNext = new Block(RENDERER);
	pCur = pNext;
	pNext = new Block(RENDERER);
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

void PlayerBlock::nextNew(SDL_Renderer* RENDERER) {
	delete pCur;
	pCur = pNext;
	pNext = new Block(RENDERER);
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
