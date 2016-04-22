#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture2D
{
private:
int		mWidth;
int		mHeight;

SDL_Renderer* mRenderer;
SDL_Texture* mTexture;

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile( std::string path );
	void Free();
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);

	int GetWidth()	{return mWidth;}
	int GetHeight() {return mHeight;}
};

#endif
