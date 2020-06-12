#include "Game.h"

int Game::Width = 0;
int Game::Height = 0;
SDL_Renderer* Game::renderer = nullptr;

Game::Game(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
	Game::Width = width;
	Game::Height = height;
	std::cout << Game::Width << ", " << Game::Height << '\n';

	m_OrthoSize = 7;
	camera = new Camera(m_OrthoSize);

	input = new Input();

	background = new BackgroundObject();
	player = new PlayerObject();

	m_NumFloors = 20;
	for (int i = 0; i < m_NumFloors; i++) floors[i] = new FloorObject();

	m_NumPipes = 3;
	m_PipeSpacing = 6;
	m_MaxPipePos = 4;
	for (int i = 0; i < m_NumPipes; i++) pipes[i] = new PipeObject();

	m_Score = m_HighScore = 0;
	m_TimeSinceScore = 0;

	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	renderManager = new RenderManager();
	isRunning = false;

	renderer = nullptr;
	window = nullptr;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window) std::cout << "Window created.\n";

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) std::cout << "Renderer created.\n";
		isRunning = true;
	}

	SDL_Init(SDL_INIT_AUDIO);
	if (TTF_Init() < 0) std::cout << "TTF ERROR: " << TTF_GetError() << '\n';
}

Game::~Game() {
	//Free all the surfaces and textures used by the UI
	SDL_FreeSurface(m_TitleSurface);
	SDL_DestroyTexture(m_TitleTexture);
	SDL_FreeSurface(m_BeginSurface);
	SDL_DestroyTexture(m_BeginTexture);
	SDL_FreeSurface(m_HighScoreSurface);
	SDL_DestroyTexture(m_HighScoreTexture);
	SDL_FreeSurface(m_ScoreSurface);
	SDL_DestroyTexture(m_ScoreTexture);

	//Free the audio devices and wavs used for the sound effects
	SDL_CloseAudioDevice(jumpID);
	SDL_FreeWAV(jumpBuffer);
	SDL_CloseAudioDevice(dieID);
	SDL_FreeWAV(dieBuffer);
	SDL_CloseAudioDevice(pointID);
	SDL_FreeWAV(pointBuffer);
}

void Game::Initialise() {
	player->Initialise(renderer, Vector2(-3, 0), Vector2(1, 1));

	for (int i = 0; i < m_NumPipes; i++) {
		int side = Random() / 1000 >= m_MaxPipePos / 2 ? 1 : -1;
		pipes[i]->Initialise(renderer, Vector2(10 + (i * m_PipeSpacing), side * (Random() / 1000)), Vector2(1.5f, 20));
	}

	float backgroundWidth = (m_OrthoSize * ((float)Height / Width)) / 1.5f;
	background->Initialise(renderer, Vector2(0, 0), Vector2(backgroundWidth, m_OrthoSize * 2));
	for (int i = 0; i < m_NumFloors; i++) floors[i]->Initialise(renderer, Vector2((-m_NumFloors / 2) + i, -m_OrthoSize + 0.5f), Vector2(1, 1));

	//Initialise the UI elements
	font = TTF_OpenFont("Assets/Pixellari.ttf", 50);
	
	m_TitleSurface = TTF_RenderText_Solid(font, "SDL FLAPPY", { 255, 255, 255 });
	m_TitleTexture = SDL_CreateTextureFromSurface(renderer, m_TitleSurface);
	m_TitleRect = { Width / 2 - m_TitleSurface->w / 2, Height / 2 - m_TitleSurface->h / 2, m_TitleSurface->w, m_TitleSurface->h };

	m_BeginSurface = TTF_RenderText_Solid(font, "PRESS SPACE OR CLICK TO BEGIN", { 255, 255, 255 });
	m_BeginTexture = SDL_CreateTextureFromSurface(renderer, m_BeginSurface);
	m_BeginRect = { Width / 2 - m_BeginSurface->w / 4, Height / 2 + m_TitleSurface->h / 2, m_BeginSurface->w / 2, m_BeginSurface->h / 2 };

	UpdateHighScoreUI();

	UpdateScoreUI();

	//Initialise the audio elements
	SDL_LoadWAV("Assets/jump.wav", &jumpSpec, &jumpBuffer, &jumpLength);
	SDL_LoadWAV("Assets/die.wav", &dieSpec, &dieBuffer, &dieLength);
	SDL_LoadWAV("Assets/point.wav", &pointSpec, &pointBuffer, &pointLength);

	jumpID = SDL_OpenAudioDevice(NULL, 0, &jumpSpec, NULL, 0);
	dieID = SDL_OpenAudioDevice(NULL, 0, &dieSpec, NULL, 0);
	pointID = SDL_OpenAudioDevice(NULL, 0, &pointSpec, NULL, 0);
}

void Game::Update() {
	background->Update();
	player->Update();

	//When the jump button is pressed play the sound effect
	if (Input::GetKeyDown(Input::KeyCode::Space) || Input::GetMouseButtonDown(0)) PlayAudio(jumpID, jumpBuffer, jumpLength);

	if (isMainMenu) {
		//Begin the game on input 
		if (Input::GetKeyDown(Input::KeyCode::Space) || Input::GetMouseButtonDown(0)) isMainMenu = false;

		//The player cannot move during this time and reposition the pipes
		player->SetCanMove(false);
		for (int i = 0; i < m_NumPipes; i++) {
			int side = Random() / 1000 >= m_MaxPipePos / 2 ? 1 : -1;
			pipes[i]->SetPosition(Vector2(10 + (i * m_PipeSpacing), side * (Random() / 1000)));
		}
	}
	else {
		player->SetCanMove(true);		//Allow the player to move

		m_TimeSinceScore += Time::GetDeltaTime();	//Increase the time since the last score

		for (int i = 0; i < m_NumPipes; i++) {
			pipes[i]->Update();	//Update the pipes

			//Check for collision between the player and any pipe
			if (player->GetBox().IsColliding(pipes[i]->GetBottomBox()) || player->GetBox().IsColliding(pipes[i]->GetTopBox())) {
				Reset();
			}

			//If the player has passed a pipe, increase their score
			if (player->GetBox().GetTopLeft().x >= pipes[i]->GetBottomBox().GetBottomRight().x && m_TimeSinceScore >= 0.5f) {
				PlayAudio(pointID, pointBuffer, pointLength);
				m_Score++;
				UpdateScoreUI();
				//std::cout << "SCORE: " << m_Score << '\n';
				m_TimeSinceScore = 0;
			}

			//Once the pipe has gone far enough, reset it's position
			if (pipes[i]->GetPos().x <= -5) {
				int previousIndex = i == 0 ? m_NumPipes - 1 : i - 1;
				int side = Random() / 1000 >= m_MaxPipePos / 2 ? 1 : -1;
				Vector2 newPos = Vector2(pipes[previousIndex]->GetPos().x + m_PipeSpacing, side * (Random() / 1000));
				pipes[i]->SetPosition(newPos);
			}
		}
	}

	//Update the floor positions
	for (int i = 0; i < m_NumFloors; i++) {
		floors[i]->Update();

		if (floors[i]->GetPos().x <= -5.0f) {
			int previousIndex = i == 0 ? m_NumFloors - 1 : i - 1;
			Vector2 newPos = Vector2(floors[previousIndex]->GetPos().x + 1, floors[i]->GetPos().y);
			floors[i]->SetPosition(newPos);
		}
	}

	if (player->GetPos().y >= m_OrthoSize || player->GetPos().y <= -m_OrthoSize + 1) Reset();
}

void Game::Reset() {
	PlayAudio(dieID, dieBuffer, dieLength);	//Play the death audio
				//Update the high score
	if (m_Score > m_HighScore) {
		m_HighScore = m_Score;
		m_Score = 0;
		UpdateScoreUI();
		UpdateHighScoreUI();
	}
	isMainMenu = true;	//Return to the main menu
}

//This function handles input events and passes it to the input manager class
void Game::HandleEvents() {
	input->BeginInput();	//Begin input detection
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) isRunning = false;

		//Store all the keys pressed this frame
		if (event.type == SDL_KEYDOWN) input->AddKeyPressed(event.key.keysym.sym);

		//Store the keys released this frame
		if (event.type == SDL_KEYUP) input->AddKeyReleased(event.key.keysym.sym);

		//The mouse buttons pressed this frame
		if (event.type == SDL_MOUSEBUTTONDOWN) input->AddMouseButton(event.button.button);

		//The mouse buttons released this frame
		if (event.type == SDL_MOUSEBUTTONUP) input->RemoveMouseButton(event.button.button);
	}

	//Get the mouse position in the window
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	input->SetMousePosition(Vector2(mouseX, mouseY));

	//If escape is pressed, quit the game
	if (input->GetKeyUp(Input::KeyCode::Escape)) isRunning = false;
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);	//Set the background colour
	SDL_RenderClear(renderer);							//Clear the render view

	//The render manager renders all objects in the game (if they've been added)
	renderManager->Render(renderer);

	//Rendering these allows you to visualise the box colliders of the objects
	/*for (int i = 0; i < m_NumPipes; i++) {
		pipes[i]->Render(renderer);
	}*/
	//player->Render(renderer);

	//This renders a box to show the orthographic size
	//camera->Render(renderer);

	//Render the UI depending on what scene is currently active
	if (isMainMenu) {
		SDL_RenderCopy(renderer, m_TitleTexture, NULL, &m_TitleRect);
		SDL_RenderCopy(renderer, m_BeginTexture, NULL, &m_BeginRect);
		SDL_RenderCopy(renderer, m_HighScoreTexture, NULL, &m_HighScoreRect);
	}
	else {
		SDL_RenderCopy(renderer, m_ScoreTexture, NULL, &m_ScoreRect);
	}
	

	SDL_RenderPresent(renderer);						//Render the frame
}

//This function is called when the game exits
void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned.\n";
}

//Update the score UI
void Game::UpdateScoreUI() {
	std::string scoreText = std::to_string(m_Score);
	m_ScoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), { 255, 255, 255 });
	m_ScoreTexture = SDL_CreateTextureFromSurface(renderer, m_ScoreSurface);
	m_ScoreRect = { Width / 2 - m_ScoreSurface->w, Height / 8 - m_ScoreSurface->h, m_ScoreSurface->w * 2, m_ScoreSurface->h * 2 };
	SDL_FreeSurface(m_ScoreSurface);
}

//Update the high score UI
void Game::UpdateHighScoreUI() {
	std::string highscoreText = "HIGH SCORE: ";
	highscoreText += std::to_string(m_HighScore);
	m_HighScoreSurface = TTF_RenderText_Solid(font, highscoreText.c_str(), { 255, 255, 255 });
	m_HighScoreTexture = SDL_CreateTextureFromSurface(renderer, m_HighScoreSurface);
	m_HighScoreRect = { Width / 2 - m_HighScoreSurface->w / 4, Height - m_HighScoreSurface->h / 2, m_HighScoreSurface->w / 2, m_HighScoreSurface->h / 2 };
	SDL_FreeSurface(m_HighScoreSurface);
}

void Game::PlayAudio(SDL_AudioDeviceID id, Uint8* buffer, Uint32 length) {
	SDL_ClearQueuedAudio(id);	//Stop the sound if its already playing
	int success = SDL_QueueAudio(id, buffer, length);	//Queue the new sound
	SDL_PauseAudioDevice(id, 0);	//Play the new sound
}

//This function generates a random number between zero and max (multiplied by 1000)
int Game::Random() {
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return rand() % ((int)(m_MaxPipePos * 1000) + 1);
}