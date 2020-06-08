#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "Time.h"
#include <iostream>
#include "Camera.h"
#include "RenderManager.h"
#include "BackgroundObject.h"
#include "PlayerObject.h"
#include "PipeObject.h"
#include "Input.h"
#include "FloorObject.h"

class Game {
public:
	Game(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	~Game();

	void Initialise();
	void Update();
	void HandleEvents();
	void Render();
	void Clean();
	bool Running() { return isRunning; }

	static SDL_Renderer* renderer;
	static int Width, Height;

private:
	bool isRunning = false;
	bool isMainMenu = true;
	SDL_Window* window;
	int m_OrthoSize;
	int Random();			//Generate a random number for the pipe position

	int m_NumPipes;			//The number of pipes
	float m_PipeSpacing;	//The space between each pipe
	float m_MaxPipePos;		//The maximum the pipe position on the y axis

	int m_NumFloors;		//The number of floor tiles

	RenderManager* renderManager;
	Camera* camera;
	BackgroundObject* background;
	PlayerObject* player;
	FloorObject* floors[10];
	PipeObject* pipes[3];
	Input* input;
};

#endif // !GAME_H