#pragma once
#include "SDL_mixer.h"
#include <memory>

struct chunk_deleter {
	void operator()(Mix_Chunk* b) const;
};

class MTSSound
{
	MTSSound(const char* filename);

private:
	std::unique_ptr<Mix_Chunk> chunk;
};

