#pragma once
#ifndef FLOOR_OBJECT_H
#define FLOOR_OBJECT_H

#include "GameObject.h"
#include "BoxCollider2D.h"
#include "Input.h"

class FloorObject : public GameObject
{
public:
	FloorObject();
	~FloorObject();
	void Initialise(SDL_Renderer* renderer, Vector2 position, Vector2 size);
	void Update();
	void SetPosition(Vector2 position);

private:
	float m_MoveSpeed;
};

#endif // !FLOOR_OBJECT_H