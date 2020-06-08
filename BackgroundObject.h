#pragma once
#ifndef BACKGROUND_OBJECT_H
#define BACKGROUND_OBJECT_H

#include "GameObject.h"
#include "BoxCollider2D.h"
#include "Input.h"

class BackgroundObject : public GameObject
{
public:
	BackgroundObject();
	~BackgroundObject();
	void Initialise(SDL_Renderer* renderer, Vector2 position, Vector2 size);
	void Render(SDL_Renderer* renderer);
};

#endif // !BACKGROUND_OBJECT_H