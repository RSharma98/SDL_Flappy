#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"
#include "RenderManager.h"
#include "SpriteRenderer.h"
#include <time.h>
#include <cstdlib>
#include "Vector2.h"

class GameObject {
public:
	GameObject();
	~GameObject();
	void Initialise(SDL_Renderer* renderer, Vector2 position, Vector2 size);
	void Update();
	void Render(SDL_Renderer* renderer);
	void Hide();
	void MakeVisible();
	Vector2 GetPos() { return m_Pos; }
	Vector2 GetSize() { return m_Size; }

protected:
	int Random(int max);
	const char* spritePath;
	SpriteRenderer* spriteRenderer;
	SDL_Rect sourceRect, destRect;
	Vector2 m_Pos;
	Vector2 m_Size;
};

#endif
