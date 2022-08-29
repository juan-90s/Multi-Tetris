#include "Block.h"
#include <stdlib.h>
#include <iostream>
#include "SDL_image.h"

SDL_Texture* Block::m_IMGS[7] = {NULL, };
int Block::m_size = 32;

Block::Block(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	if (m_IMGS[0] == NULL) {
		// Load all-in-on blocks image W: 0..255, H: 0..31
		SDL_Surface* surf = IMG_Load("assets/blocks.png");
		if (!surf) {
			std::cerr << IMG_GetError() << std::endl;
			exit(1);
		}
		m_size = surf->h;	// height should be 32
		SDL_Texture* aio_img = SDL_CreateTextureFromSurface(m_renderer, surf);
		SDL_FreeSurface(surf);
		for (int i = 0; i < 7; i++) {
			m_IMGS[i] = SDL_CreateTexture(m_renderer,
										SDL_PIXELFORMAT_RGBA8888,
										SDL_TEXTUREACCESS_TARGET,
										m_size, m_size);
			SDL_SetTextureBlendMode(m_IMGS[i], SDL_BLENDMODE_BLEND);
			SDL_Rect rect = {i * m_size, 0, m_size, m_size };  // ignore last black block
			SDL_SetRenderTarget(m_renderer, m_IMGS[i]);
			SDL_RenderCopy(m_renderer, aio_img, &rect, NULL);
		}
		SDL_DestroyTexture(aio_img);
		SDL_SetRenderTarget(m_renderer, NULL);
	}

	int blockShapes[7][4] = {
	1,3,5,7,	// 'I'
	2,4,5,7,	// 'S'
	3,5,4,6,	// flip 'S'
	3,5,4,7,	// 'T'
	2,3,5,7,	// 'L'
	3,5,7,6,	// flip 'L'
	2,3,4,5,	// square
	};


	// randomly generate one type of blocks
	m_blockType = 1 + (int)(7.0 * (rand() / (RAND_MAX + 1.0)));	// 1..7
	// intialize basicBlocks' point (begin from 0)
	for (int i = 0; i < 4; i++) {
		int value = blockShapes[m_blockType - 1][i];
		m_blockPoints[i].row = value / 2;
		m_blockPoints[i].col = value % 2;
	}

	m_blockIMG = m_IMGS[m_blockType - 1];

}

void Block::drop()
{
	for (int i = 0; i < 4; i++) {
		m_blockPoints[i].row++;
	}
}

void Block::moveLeftRight(const int offset)
{
	for (int i = 0; i < 4; i++) {
		m_blockPoints[i].col += offset;
	}
}

void Block::rotate()
{
	Point center = m_blockPoints[1];

	for (int i = 0; i < 4; i++) {
		Point tmp = m_blockPoints[i];
		m_blockPoints[i].col = center.col - tmp.row + center.row;
		m_blockPoints[i].row = center.row + tmp.col - center.col;
	}
}

void Block::draw(int leftMargin, int topMargin)
{
	SDL_Rect dstRect = { 0, };
	SDL_QueryTexture(m_blockIMG, NULL, NULL, &dstRect.w, &dstRect.h);
	for (int i = 0; i < 4; i++) {
		dstRect.x = leftMargin + m_blockPoints[i].col * m_size;
		dstRect.y = topMargin + m_blockPoints[i].row * m_size;
		SDL_RenderCopy(m_renderer, m_blockIMG, NULL, &dstRect);
	}
}

int Block::getType() const
{
	return m_blockType;
}

Point* Block::getPoints()
{
	return m_blockPoints;
}

SDL_Texture** Block::getIMGs()
{
	return m_IMGS;
}

Block& Block::operator=(const Block& other)
{
	if (this == &other) return *this;
	this->m_blockType = other.m_blockType;
	for (int i = 0; i < 4; i++) {
		this->m_blockPoints[i] = other.m_blockPoints[i];
	}
	return *this;
}
