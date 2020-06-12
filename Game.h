#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>
#include "Time.h"
#include <iostream>
#include <string>
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

	float m_TimeSinceScore;	//The time since the score was last increased
	int m_Score;			//The score and highscore of the player
	int m_HighScore;

	void Reset();			//Reset the game when the player dies
	void UpdateScoreUI();
	void UpdateHighScoreUI();

	TTF_Font* font;						//The font used for the game UI
	SDL_Surface* m_TitleSurface;		//The surface for the game title
	SDL_Surface* m_HighScoreSurface;	//The surface for the high score
	SDL_Surface* m_BeginSurface;		//The surface for the text to begin the game
	SDL_Texture* m_TitleTexture;
	SDL_Texture* m_HighScoreTexture;
	SDL_Texture* m_BeginTexture;
	SDL_Surface* m_ScoreSurface;
	SDL_Texture* m_ScoreTexture;
	SDL_Rect m_TitleRect, m_HighScoreRect, m_BeginRect, m_ScoreRect;

	void PlayAudio(SDL_AudioDeviceID id, Uint8* buffer, Uint32 length);	//Play the specified sound effect

	SDL_AudioDeviceID jumpID;
	SDL_AudioSpec jumpSpec;			//The variables for the game sound effects
	Uint32 jumpLength;
	Uint8* jumpBuffer;
	SDL_AudioDeviceID pointID;
	SDL_AudioSpec pointSpec;
	Uint32 pointLength;
	Uint8* pointBuffer;
	SDL_AudioDeviceID dieID;
	SDL_AudioSpec dieSpec;
	Uint32 dieLength;
	Uint8* dieBuffer;

	RenderManager* renderManager;
	Camera* camera;
	BackgroundObject* background;
	PlayerObject* player;
	FloorObject* floors[20];
	PipeObject* pipes[3];
	Input* input;
};

#endif // !GAME_H