#include "Camera.h"
#include "Game.h"

Camera* Camera::Instance = NULL;

Camera::Camera(float orthoSize)
{
	if (Instance == NULL) Camera::Instance = this;
	this->orthoSize = orthoSize;
	this->position = Vector2(0, 0);
	this->unitSize = Game::Height / (orthoSize * 2.0f);
}

void Camera::Render(SDL_Renderer* renderer) {
	Vector2 updatedPos = WorldToScreenUnits(position);
	Vector2 topLeft(updatedPos.x - (unitSize / 2.0f), updatedPos.y - (unitSize / 2.0f));
	Vector2 bottomRight(updatedPos.x + (unitSize / 2.0f), updatedPos.y + (unitSize / 2.0f));
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(renderer, topLeft.x, topLeft.y, bottomRight.x, topLeft.y);
	SDL_RenderDrawLine(renderer, bottomRight.x, topLeft.y, bottomRight.x, bottomRight.y);
	SDL_RenderDrawLine(renderer, bottomRight.x, bottomRight.y, topLeft.x, bottomRight.y);
	SDL_RenderDrawLine(renderer, topLeft.x, bottomRight.y, topLeft.x, topLeft.y);
}
//Convert from world units to on screen co-ordinates
Vector2 Camera::WorldToScreenUnits(Vector2 v) {
	return Vector2((Game::Width / 2) + (v.x * unitSize) - position.x, (Game::Height / 2) - (v.y * unitSize) + position.y);
}

//Convert from screen to world units
Vector2 Camera::ScreenToWorldUnits(Vector2 v) {
	return Vector2(position.x + (v.x / unitSize) - (Game::Width / 2) / unitSize, position.y - (v.y / unitSize) + (Game::Height / 2) / unitSize);
}
