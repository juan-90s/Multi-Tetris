#pragma once
#include "SDL.h"
#include <vector>
#include "Block.h"
class PlayerBlock
{
	// TODO: refactor PlayerBlock, current design is not good
public:
	PlayerBlock(SDL_Renderer* m_renderer);
	void clean();

	inline void backup();	// backup current block to backup
	void recover();			// recover backup to current
	void nextNew(SDL_Renderer* m_renderer);
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
	Tetris() = default;
	Tetris(SDL_Renderer* m_renderer, int rows, int cols, int left, int top, int blockSize);
	void init();	// initialize game
	void clean();
	void draw();

	void drop(PlayerBlock& pBlock);
	void moveLeftRight(PlayerBlock& pBlock, int offset);
	void rotate(PlayerBlock& pBlock);
	void clearLine();

	PlayerBlock& player(const int num);
private:
	bool checkBlock(Block* block) const;
	void fixBlock(Block* block);
private:
	SDL_Renderer* m_renderer = 0;
	PlayerBlock playerBlock = 0;

	std::vector< std::vector<int> > m_grid;  // store block type(1..7) in 2-d map. 0 means empty
	int m_rows;
	int m_cols;
	int m_leftMargin;
	int m_topMargin;
	int m_blockSize;
	SDL_Texture* m_frameIMG;
};


