#pragma once

#include "SDL.h"
#include "SDL_mixer.h"

#include <string>
using namespace std;

class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();

	void Play(int loops);
	void Stop();
	void Load(string path);

private:
	Mix_Chunk* sfx;
	int channel;
};


