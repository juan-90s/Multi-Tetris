#pragma once
#include <vector>
#include <memory>
#include "Block.h"
#include "MTSLabel.h"
#include "MTSScene.h"
class PlayerBlock
{
	// TODO: refactor PlayerBlock, current design is not good
public:
	PlayerBlock();

	inline void backup();	// backup current block to backup
	void recover();			// recover backup to current
	void nextNew();
	void unlockControl();
	bool speedControl();	// control frequency to do periodic jobs
							// true means being controlled as well as not to do

	std::unique_ptr<Block> pCur = nullptr;
	std::unique_ptr<Block> pNext = nullptr;
	Block pBak;

	int pSpeedMulti = 20;
	int pSpeedWindw = 0;
};

class Tetris : public MTSScene
{
public:
	Tetris() = default;
	Tetris(const SDL_Rect& rect, const int rows, const int cols, const int blockSize);

	void init() override;
	void draw() override;
	void update() override;
	void handleEvent(SDL_Event& event) override;

	void moveLeftRight(PlayerBlock& pBlock, int offset);
	void rotate(PlayerBlock& pBlock);
	

	PlayerBlock& player(const int num);
private:
	void drop(PlayerBlock& pBlock);
	void clearLine();
	bool checkBlock(Block* block) const;
	void fixBlock(Block* block);
private:
	PlayerBlock playerBlock;

	bool m_bRunning = 0;

	std::vector< std::vector<int> > m_vec2dGrid;  // store block type(1..7) in 2-d map. 0 means empty
	int m_iRows = 0;
	int m_iCols = 0;
	int m_iBlockSize = 0;

	MTSLabel m_labelScore;

	int m_iScore = 0;
};


