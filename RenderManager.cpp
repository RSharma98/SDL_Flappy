#include "RenderManager.h"
#include <iostream>

RenderManager* RenderManager::Instance = NULL;

struct RenderManager::Sprite {
public:
	SpriteRenderer* spriteRenderer;
	Vector2 position;
	Vector2 size;
};

RenderManager::RenderManager() {
	if (RenderManager::Instance == NULL) RenderManager::Instance = this;
	sprites = std::vector<Sprite>();
}

void RenderManager::AddToRenderQueue(SpriteRenderer* spriteRenderer, Vector2 position, Vector2 size) {
	Sprite sprite;
	sprite.spriteRenderer = spriteRenderer;
	sprite.position = position;
	sprite.size = size;
	sprites.push_back(sprite);
}

void RenderManager::Render(SDL_Renderer* renderer) {
	Camera* cam = Camera::Instance;
	for (int i = 0; i < sprites.size(); i++) {
		Sprite sprite = sprites[i];
		Vector2 screenPos = cam->WorldToScreenUnits(sprite.position);
		Vector2 spriteSize = sprite.size * cam->GetUnitSize();
		SDL_Rect destRect;
		destRect.x = screenPos.x - spriteSize.x / 2;
		destRect.y = screenPos.y - spriteSize.y / 2;
		destRect.w = spriteSize.x;
		destRect.h = spriteSize.y;
		SDL_RenderCopy(renderer, sprite.spriteRenderer->sprite, &sprite.spriteRenderer->sourceRect, &destRect);
	}
	sprites.clear();
}