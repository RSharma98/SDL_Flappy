#include "SpriteRenderer.h"

//Initialise a sprite rendererer so an image can be loaded based on the image path and specified rects
void SpriteRenderer::Initialise(const char* path, SDL_Renderer *renderer, SDL_Rect sourceRect) {
	SDL_Surface* surface = IMG_Load(path);
	sprite = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	this->sourceRect = sourceRect;
	flipX = flipY = false;
	renderSprite = true;
	colour = SDL_Color{ 255, 255, 255, 255 };
}

void SpriteRenderer::UpdateSourceRect(SDL_Rect source) {
	this->sourceRect = source;
}

//Render the sprite
/*void SpriteRenderer::Render(SDL_Renderer *renderer) {
	if(renderSprite) SDL_RenderCopy(renderer, sprite, &sourceRect, &destinationRect);
}*/
