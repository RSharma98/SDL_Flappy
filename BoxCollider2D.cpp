#include "BoxCollider2D.h"
#include "Debug.h"

void BoxCollider2D::Initialise(Vector2 position, Vector2 offset, Vector2 size) {
	Camera* cam = Camera::Instance;
	this->position = position;
	this->offset = offset;
	this->size = size;
}

void BoxCollider2D::Update() {
	Camera* cam = Camera::Instance;
}


Vector2 BoxCollider2D::GetTopLeft(){
	return Vector2(position.x + offset.x - (size.x / 2.0f), position.y + offset.y - (size.y / 2.0f));
}

Vector2 BoxCollider2D::GetBottomRight(){
	return Vector2(position.x + offset.x + (size.x / 2.0f), position.y + offset.y + (size.y / 2.0f));
}

void BoxCollider2D::Render(SDL_Renderer* renderer, SDL_Color drawColour){
	Debug::DrawRectangle(position + offset, size);
}

bool BoxCollider2D::IsColliding(BoxCollider2D other)
{
	if (GetTopLeft().x > other.GetBottomRight().x || GetBottomRight().x < other.GetTopLeft().x || GetBottomRight().y < other.GetTopLeft().y || GetTopLeft().y > other.GetBottomRight().y) return false;
	return true;
}
