#include "PlayerObject.h"
#include <iostream>
#include "MathHelper.h"
#include "Time.h"

PlayerObject::PlayerObject() {
	m_Vel = Vector2(0, 0);
	m_FallSpeed = 28.0f;
	m_JumpHeight = 8.0f;
}

PlayerObject::~PlayerObject(){

}

void PlayerObject::Initialise(SDL_Renderer* renderer, Vector2 position, Vector2 size) {
	spritePath = "Assets/Flappy_Bird_Spritesheet.png";
	sourceRect = SDL_Rect{ 113, 325, 20, 20 };
	GameObject::Initialise(renderer, position, size);
	box.Initialise(position, Vector2(0, 0), size * 0.65f);
}

void PlayerObject::Update() {
	//Depending on input jump or fall
	if (Input::GetKeyDown(Input::KeyCode::Space) || Input::GetMouseButtonDown(0)) m_Vel.y = m_JumpHeight;
	else m_Vel.y -= m_FallSpeed * Time::GetDeltaTime();

	//Add the velocity to the position
	m_Pos += m_Vel * Time::GetDeltaTime();

	//Replace this with a game over state
	if (m_Pos.y <= -7 || m_Pos.y >= 7) m_Pos.y = 7 * MathHelper::Sign(m_Pos.y);
	
	box.position = m_Pos;
	GameObject::Update();
	box.Update();
}

void PlayerObject::Render(SDL_Renderer* renderer) {
	GameObject::Render(renderer);
	box.Render(renderer, SDL_Color{ 0, 255, 0, 255 });
}

void PlayerObject::SetPosition(Vector2 position) { 
	m_Pos = position; 
	Update();
}
