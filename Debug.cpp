#include "Debug.h"

void Debug::DrawRectangle(Vector2 position, Vector2 size) {
	SDL_Renderer* renderer = Game::renderer;
	position = Camera::Instance->WorldToScreenUnits(position);
	size = size * Camera::Instance->GetUnitSize();
	Vector2 topLeft = Vector2(position.x - (size.x / 2), position.y + (size.y / 2));
	Vector2 bottomRight = Vector2(position.x + (size.x / 2), position.y - (size.y / 2));
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, topLeft.x, topLeft.y, bottomRight.x, topLeft.y);
	SDL_RenderDrawLine(renderer, bottomRight.x, topLeft.y, bottomRight.x, bottomRight.y);
	SDL_RenderDrawLine(renderer, bottomRight.x, bottomRight.y, topLeft.x, bottomRight.y);
	SDL_RenderDrawLine(renderer, topLeft.x, bottomRight.y, topLeft.x, topLeft.y);
}