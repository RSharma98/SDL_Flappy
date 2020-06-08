#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2.h"
#include "SDL.h"

class Camera {
public:
	Camera(float orthoSize);
	void Render(SDL_Renderer* renderer);
	Vector2 WorldToScreenUnits(Vector2 v);
	Vector2 ScreenToWorldUnits(Vector2 v);

	static Camera* Instance;
	Vector2 position;
	float orthoSize;
	float GetUnitSize() { return unitSize; }

private:
	float unitSize;
};
#endif // !CAMERA_H
