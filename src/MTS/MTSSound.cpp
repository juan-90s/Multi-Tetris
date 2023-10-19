#include "MTSSound.h"

void chunk_deleter::operator()(Mix_Chunk* b) const
{
	Mix_FreeChunk(b);
}
