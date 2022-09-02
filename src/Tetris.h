#pragma once
#include <vector>
#include <memory>
#include "Block.h"
class PlayerBlock
{
	// TODO: refactor PlayerBlock, current design is not good
public:
	PlayerBlock();
	void clean();

	inline void backup();	// backup current block to backup
	void recover();			// recover backup to current
	void nextNew();
	void unlockControl();
	bool speedControl();	// control frequency to do periodic jobs
							// true means being controlled as well as not to do

	std::unique_ptr<Block> pCur = nullptr;
	std::unique_ptr<Block> pNext = nullptr;
	Block pBak;

	int pSpeedMulti = 4;
	int pSpeedWindw = 0;
};

class Tetris
{
public:
	Tetris() = default;
	Tetris(int rows, int cols, int left, int top, int blockSize);
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
	PlayerBlock playerBlock;

	std::vector< std::vector<int> > m_grid;  // store block type(1..7) in 2-d map. 0 means empty
	int m_rows = 0;
	int m_cols = 0;
	int m_leftMargin = 0;
	int m_topMargin = 0;
	int m_blockSize = 0;
};


