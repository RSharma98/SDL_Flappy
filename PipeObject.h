#pragma once
#ifndef PIPE_OBJECT_H
#define PIPE_OBJECT_H

#include "GameObject.h"
#include "BoxCollider2D.h"
#include "Input.h"

class PipeObject
{
public:
	PipeObject();
	~PipeObject();
	void Initialise(SDL_Renderer* renderer, Vector2 position, Vector2 size);
	void Update();
	void Render(SDL_Renderer* renderer);
	void SetPosition(Vector2 position);

	Vector2 GetPos() { return m_Pos; }
	Vector2 GetSize() { return m_Size; }
	BoxCollider2D GetTopBox() { return m_TopBox; }
	BoxCollider2D GetBottomBox() { return m_BottomBox; }

private:
	const char* spritePath;
	BoxCollider2D m_BottomBox, m_TopBox;
	SpriteRenderer* m_BottomSprite, *m_TopSprite;
	SDL_Rect m_BottomSource, m_TopSource;
	SDL_Rect m_BottomDest, m_TopDest;
	Vector2 m_Pos, m_Size;
};

#endif // !PIPE_OBJECT_H