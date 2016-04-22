#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Texture2D.h"
using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture2D::~Texture2D()
{
	if(mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	Free();
	mRenderer = NULL;
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//Set where to render the texture
	SDL_Rect renderLocation = {newPosition.x, newPosition.y, mWidth, mHeight};

	//Render to the screen.
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);	
}

bool Texture2D::LoadFromFile( std::string path )
{
	SDL_Texture* pTexture = NULL;

	//Load the image.
	SDL_Surface* pSurface = IMG_Load( path.c_str());
	if(pSurface != NULL)
	{
		//Makes image transparent.
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		//Create the texture from the pixels on the surface.
		pTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if(pTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
			
		}

		//Set the dimensions.
		mWidth = pSurface->w;
		mHeight = pSurface->h;

		//Remove the loaded surfcae now that we have the texture.
		SDL_FreeSurface(pSurface);
	}

	//Sets the internal texture.
	mTexture = pTexture;
	return mTexture != NULL;
}

void Texture2D::Free()
{
}