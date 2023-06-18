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
	~Block() = default;
	void drop();
	void moveLeftRight(int offset);
	void rotate();
	void render(int leftMargin, int topMargin, int size=m_size);

	int getType() const;
	void setShape(const int type);
	void setColor(const BlockColor color);

	Point* getPoints();
	static MTSTexture* getIMGs();

	Block& operator=(const Block& other);

private:
	void loadIMGS();

	int m_blockColor;	// block type, indicate the color
	Point m_blockPoints[4];  // coorinate of blocks in pieces
	MTSTexture m_blockIMG;

	static MTSTexture m_IMGS[8];  // all 1+7 color block, the extra one is wall block
	static int m_shapes[7][4];
	static int m_size;
};

