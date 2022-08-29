#pragma once
#include "SDL.h"
#include <vector>

struct Point {
	int row;
	int col;
};

class Block
{
public:
	Block(SDL_Renderer* renderer);
	void drop();
	void moveLeftRight(int offset);
	void rotate();
	void draw(int leftMargin, int topMargin);

	int getType() const;
	Point* getPoints();
	static SDL_Texture** getIMGs();

	Block& operator=(const Block& other);

private:
	int m_blockType;	// block type, differently shaped pieces
	Point m_blockPoints[4];  // coorinate of blocks in pieces
	SDL_Texture* m_blockIMG;
	SDL_Renderer* m_renderer;

	static SDL_Texture* m_IMGS[7];  // all seven color block
	static int m_size;
};

