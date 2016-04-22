#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	sfx = NULL;
	channel = -1;
}


SoundEffect::~SoundEffect()
{
}

void SoundEffect::Play(int loops)
{
	channel = Mix_PlayChannel(-1, sfx, loops);
}

void SoundEffect::Stop()
{
	Mix_HaltChannel(channel);
}

void SoundEffect::Load(string path)
{
	sfx = Mix_LoadWAV(path.c_str());
}
