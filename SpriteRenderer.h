#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "SDL.h"
#include "SDL_image.h"

class SpriteRenderer {
public:
	void Initialise(const char* path, SDL_Renderer* renderer, SDL_Rect source);
	void UpdateSourceRect(SDL_Rect source);

	SDL_Texture* sprite;
	SDL_Rect sourceRect;
	bool flipX = false;
	bool flipY = false;
	bool renderSprite = true;
	SDL_Color colour;
};

#endif 