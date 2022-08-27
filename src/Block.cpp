#include "Block.h"
#include <stdlib.h>
#include <iostream>

SDL_Texture* Block::imgs[7] = {NULL, };
int Block::size = 32;

Block::Block(SDL_Renderer* renderer)
{
	RENDERER = renderer;
	if (imgs[0] == NULL) {
		// Load all-in-on blocks image W: 0..255, H: 0..31
		SDL_Surface* surf = IMG_Load("assets/blocks.png");
		if (!surf) {
			std::cerr << IMG_GetError() << std::endl;
			exit(1);
		}
		/*int width = surf->w;	// width should be 255*/
		int height = surf->h;	// height should be 32
		SDL_Texture* aio_img = SDL_CreateTextureFromSurface(RENDERER, surf);
		SDL_FreeSurface(surf);
		for (int i = 0; i < 7; i++) {
			size = height;
			imgs[i] = SDL_CreateTexture(RENDERER,
										SDL_PIXELFORMAT_RGBA8888,
										SDL_TEXTUREACCESS_TARGET,
										size, size);
			SDL_SetTextureBlendMode(imgs[i], SDL_BLENDMODE_BLEND);
			SDL_Rect rect = {i * size, 0, size, size };  // ignore last black block
			SDL_SetRenderTarget(RENDERER, imgs[i]);
			SDL_RenderCopy(RENDERER, aio_img, &rect, NULL);
		}
		SDL_DestroyTexture(aio_img);
		SDL_SetRenderTarget(RENDERER, NULL);
	}

	int blocks[7][4] = {
	1,3,5,7,	// 'I'
	2,4,5,7,	// 'S'
	3,5,4,6,	// flip 'S'
	3,5,4,7,	// 'T'
	2,3,5,7,	// 'L'
	3,5,7,6,	// flip 'L'
	2,3,4,5,	// square
	};


	// randomly generate one type of blocks
	blockType = rand() % 7 + 1;	// 1..7
	// intialize basicBlocks' point (begin from 0)
	for (int i = 0; i < 4; i++) {
		int value = blocks[blockType - 1][i];
		blockPoints[i].row = value / 2;
		blockPoints[i].col = value % 2;
	}

	img = imgs[blockType - 1];

}

Block::~Block()
{
	
}

void Block::drop()
{
	for (int i = 0; i < 4; i++) {
		blockPoints[i].row++;
	}
}

void Block::moveLeftRight(int offset)
{
	for (int i = 0; i < 4; i++) {
		blockPoints[i].col += offset;
	}
}

void Block::rotate()
{
	Point center = blockPoints[1];

	for (int i = 0; i < 4; i++) {
		Point tmp = blockPoints[i];
		blockPoints[i].col = center.col - tmp.row + center.row;
		blockPoints[i].row = center.row + tmp.col - center.col;
	}
}

void Block::draw(int leftMargin, int topMargin)
{
	SDL_Rect dstRect = { 0, };
	SDL_QueryTexture(img, NULL, NULL, &dstRect.w, &dstRect.h);
	for (int i = 0; i < 4; i++) {
		dstRect.x = leftMargin + blockPoints[i].col * size;
		dstRect.y = topMargin + blockPoints[i].row * size;
		SDL_RenderCopy(RENDERER, img, NULL, &dstRect);
	}
}

int Block::getType()
{
	return blockType;
}

Point* Block::getPoints()
{
	return blockPoints;
}

SDL_Texture** Block::getIMGs()
{
	return imgs;
}

Block& Block::operator=(const Block& other)
{
	if (this == &other) return *this;
	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++) {
		this->blockPoints[i] = other.blockPoints[i];
	}
	return *this;
}
