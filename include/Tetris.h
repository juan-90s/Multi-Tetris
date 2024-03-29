#pragma once
#include <vector>
#include <memory>
#include "Block.h"
#include "MTSLabel.h"
#include "MTSScene.h"
#include "PauseMenu.h"


class PlayerBlock
{
	// TODO: refactor PlayerBlock, current design is not good
public:
	PlayerBlock();
	PlayerBlock(const BlockColor color, const int x);

	inline void backup();	// backup current block to backup
	void recover();			// recover backup to current
	void nextNew();
	void unlockControl();
	bool speedControl();	// control frequency to do periodic jobs
							// true means being controlled as well as not to do

	std::unique_ptr<Block> pCur = nullptr;
	std::unique_ptr<Block> pNext = nullptr;
	Block pBak;

	int anchorX = 0;
	BlockColor pColor = BlockColor::NoColor;

	int pDelayMulti = 20;
	int pDelayWindw = 0;
};

class Tetris : public MTSScene
{
public:
	Tetris() = delete;
	Tetris(const SDL_Rect& rect, const int rows, const int cols, const int blockSize, const unsigned int playerNum = 1);

	void init() override;
	void renderCustom() override;
	void update() override;
	void handleEvent(SDL_Event& event) override;

	void moveLeftRight(PlayerBlock& pBlock, int offset);
	void rotate(PlayerBlock& pBlock);
	void setPause(bool bFlag);
	
	
	PlayerBlock& player(const int num);
private:
	void drop(PlayerBlock& pBlock);
	void clearLine();
	bool checkInMap(Block* block) const;
	bool checkInPlayers(Block* block) const;
	void fixBlock(Block* block);
private:
	using MTSScene::m_view;
	std::vector<PlayerBlock> m_vecPlayers;

	bool m_bPause = 0;
	std::unique_ptr<PauseMenu> m_PauseMenu = nullptr;

	std::vector< std::vector<int> > m_vec2dGrid;  // store block type(1..7) in 2-d map. 0 means empty
	const int m_iRows = 0;
	const int m_iCols = 0;
	const int m_iBlockSize = 0;
	int margin_left;
	int margin_top;

	std::weak_ptr<MTSLabel> m_labelScore;
	std::weak_ptr<MTSLabel> m_labelScoreValue;

	int m_iScore = 0;
};


