#ifndef BOXCOLLIDER2D_H
#define BOXCOLLIDER2D_H

#include "Vector2.h"
#include "Camera.h"
#include "SDL.h"

class BoxCollider2D {
public:
	void Initialise(Vector2 position, Vector2 offset, Vector2 size);
	void Update();
	
	Vector2 position;
	Vector2 offset;
	Vector2 size;

	void Render(SDL_Renderer* renderer, SDL_Color drawColour);
	bool IsColliding(BoxCollider2D other);

	Vector2 GetTopLeft();
	Vector2 GetBottomRight();
};
#endif // !BOXCOLLIDER2D_H
