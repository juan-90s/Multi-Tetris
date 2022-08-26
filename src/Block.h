#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

struct Point {
	int row;
	int col;
};

class Block
{
public:
	Block(SDL_Renderer* renderer);
	~Block();
	void drop();
	void moveLeftRight(int offset);
	void rotate();
	void draw(int leftMargin, int topMargin);
	//bool isInMap(std::vector<std::vector<int>> &map);

	int getType();
	Point* getPoints();
	static SDL_Texture** getIMGs();

	Block& operator=(const Block& other);

private:
	int blockType;	// block type, differently shaped pieces
	Point blockPoints[4];  // coorinate of blocks in pieces
	SDL_Texture* img;
	SDL_Renderer* RENDERER;

	static SDL_Texture* imgs[7];  // all seven color block
	static int size;
};

