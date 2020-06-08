#include "BackgroundObject.h"

BackgroundObject::BackgroundObject()
{
}

BackgroundObject::~BackgroundObject()
{
}

void BackgroundObject::Initialise(SDL_Renderer* renderer, Vector2 position, Vector2 size)
{
	spritePath = "Assets/Flappy_Bird_Spritesheet.png";
	sourceRect = SDL_Rect{ 0, 0, 142, 250 };
	GameObject::Initialise(renderer, position, size);
}
