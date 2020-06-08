#include "FloorObject.h"
#include "Time.h"

FloorObject::FloorObject()
{
	m_MoveSpeed = 2.5f;
}

FloorObject::~FloorObject()
{
}

void FloorObject::Initialise(SDL_Renderer* renderer, Vector2 position, Vector2 size)
{
	spritePath = "Assets/Flappy_Bird_Spritesheet.png";
	sourceRect = SDL_Rect{ 298, 0, 48, 50 };
	GameObject::Initialise(renderer, position, size);
}

void FloorObject::Update() {
	m_Pos.x -= m_MoveSpeed * Time::GetDeltaTime();
	GameObject::Update();
}

void FloorObject::SetPosition(Vector2 position) {
	m_Pos = position;
	Update();
}
