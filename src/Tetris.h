#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include "Block.h"
class PlayerBlock
{
public:
	PlayerBlock(SDL_Renderer* RENDERER);
	void clean();

	inline void backup();	// backup current block to backup
	void recover();			// recover backup to current
	void nextNew(SDL_Renderer* RENDERER);
	void unlockControl();
	bool speedControl();	// control frequency to do periodic jobs
							// true means being controlled as well as not to do

	Block* pCur = nullptr;
	Block* pNext = nullptr;
	Block pBak = NULL;

	int pSpeedMulti = 4;
	int pSpeedWindw = 0;
};

class Tetris
{
public:
	Tetris(SDL_Renderer* RENDERER, int rows, int cols, int left, int top, int blockSize);
	void init();	// initialize game
	void clean();
	void draw();

	void drop(PlayerBlock& pBlock);
	void moveLeftRight(PlayerBlock& pBlock, int offset);
	void rotate(PlayerBlock& pBlock);
	void clearLine();

	PlayerBlock& player(int num);
private:
	bool checkBlock(Block* block);
	void fixBlock(Block* block);
private:
	SDL_Renderer* RENDERER = 0;
	PlayerBlock playerBlock = 0;

	std::vector<std::vector<int>> map;  // store block type(1..7) in 2-d map. 0 means empty
	int rows, cols;
	int leftMargin, topMargin;
	int blockSize;
	SDL_Texture* backgroundIMG;
	SDL_Texture* frameIMG;
};


