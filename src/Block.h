#pragma once
#include <vector>
#include "MTSTexture.h"

struct Point {
	int row;
	int col;
};

enum class BlockColor {
	NoColor, Red, Yellow, Green, Blue, Orange, Cyan, Purple
};

class Block
{
public:
	Block();
	~Block();
	void drop();
	void moveLeftRight(int offset);
	void rotate();
	void draw(int leftMargin, int topMargin, int size=m_size);

	int getType() const;
	void setType(const int type);
	void setColor(const BlockColor color);

	Point* getPoints();
	static MTSTexture* getIMGs();

	Block& operator=(const Block& other);

private:
	int m_blockType;	// block type, differently shaped pieces
	Point m_blockPoints[4];  // coorinate of blocks in pieces
	MTSTexture m_blockIMG;

	static MTSTexture m_IMGS[8];  // all 1+7 color block, the extra one is wall block
	static int m_shapes[7][4];
	static int m_size;
};

