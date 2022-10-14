#include "Block.h"
#include <stdlib.h>

MTSTexture Block::m_IMGS[8] = {};
int Block::m_shapes[7][4] = {
	1,3,5,7,	// 'I'
	2,4,5,7,	// 'S'
	3,5,4,6,	// flip 'S'
	3,5,4,7,	// 'T'
	2,3,5,7,	// 'L'
	3,5,7,6,	// flip 'L'
	2,3,4,5,	// square
};;
int Block::m_size = 32;

Block::Block()
{
	if (m_IMGS[0].isEmpty()) {
		// Load all-in-on blocks image W: 0..255, H: 0..31
		MTSTexture aio_img = MTSTexture("assets/blocks.png");
		int src_size = aio_img.getHeight();
		for (int i = 0; i < 8; i++) {
			m_IMGS[i] = MTSTexture(m_size, m_size);
			SDL_Rect rect = {i * src_size, 0, src_size, src_size };
			aio_img.copyToTexture(m_IMGS[i], &rect, NULL);
		}
	}

	// randomly generate one type of blocks
	m_blockType = 1 + (int)(7.0 * (rand() / (RAND_MAX + 1.0)));	// 1..7
	// intialize basicBlocks' point (begin from 0)
	for (int i = 0; i < 4; i++) {
		int value = m_shapes[m_blockType - 1][i];
		m_blockPoints[i].row = value / 2;
		m_blockPoints[i].col = value % 2;
	}

	m_blockIMG = m_IMGS[m_blockType];

}

Block::~Block()
{
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

void Block::draw(int leftMargin, int topMargin, int size)
{
	SDL_Rect dstRect = { 0, };
	dstRect.w = size;
	dstRect.h = size;
	for (int i = 0; i < 4; i++) {
		dstRect.x = leftMargin + m_blockPoints[i].col * size;
		dstRect.y = topMargin + m_blockPoints[i].row * size;
		m_blockIMG.copyToRenderer(NULL, &dstRect);
	}
}

int Block::getType() const
{
	return m_blockType;
}

void Block::setType(const int type)
{
	if (type > 0 && type < 8) {
		m_blockType = type;
		for (int i = 0; i < 4; i++) {
			int value = m_shapes[m_blockType - 1][i];
			m_blockPoints[i].row = value / 2;
			m_blockPoints[i].col = value % 2;
		}
	}
}

void Block::setColor(const BlockColor color)
{
	int texture_index = (int)color;
	m_blockIMG = m_IMGS[texture_index];
}

Point* Block::getPoints()
{
	return m_blockPoints;
}

MTSTexture* Block::getIMGs()
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
	this->m_blockIMG = other.m_blockIMG;
	return *this;
}
