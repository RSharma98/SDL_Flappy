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

	m_NumFloors = 10;
	for (int i = 0; i < m_NumFloors; i++) floors[i] = new FloorObject();

	m_NumPipes = 3;
	m_PipeSpacing = 6;
	m_MaxPipePos = 4;
	for (int i = 0; i < m_NumPipes; i++) pipes[i] = new PipeObject();

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
}

Game::~Game() {

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
}

void Game::Update() {
	background->Update();
	player->Update();

	for (int i = 0; i < m_NumPipes; i++) {
		pipes[i]->Update();
		if (player->GetBox().IsColliding(pipes[i]->GetBottomBox()) || player->GetBox().IsColliding(pipes[i]->GetTopBox())) isRunning = false;

		if (pipes[i]->GetPos().x <= -5) {
			int previousIndex = i == 0 ? m_NumPipes - 1 : i - 1;
			int side = Random() / 1000 >= m_MaxPipePos / 2 ? 1 : -1;
			Vector2 newPos = Vector2(pipes[previousIndex]->GetPos().x + m_PipeSpacing, side * (Random() / 1000));
			pipes[i]->SetPosition(newPos);
		}
	}

	for (int i = 0; i < m_NumFloors; i++) {
		floors[i]->Update();

		if (floors[i]->GetPos().x <= -5.0f) {
			int previousIndex = i == 0 ? m_NumFloors - 1 : i - 1;
			Vector2 newPos = Vector2(floors[previousIndex]->GetPos().x + 1, floors[i]->GetPos().y);
			floors[i]->SetPosition(newPos);
		}
	}
}

//This function handles keyboard movement (moving the player and quitting)
void Game::HandleEvents() {
	input->BeginInput();	//Begin input detection
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) isRunning = false;

		//Store all the keys pressed this frame
		if (event.type == SDL_KEYDOWN) input->AddKeyPressed(event.key.keysym.sym);

		//Store the keys released this frame
		if (event.type == SDL_KEYUP) input->AddKeyReleased(event.key.keysym.sym);

		if (event.type == SDL_MOUSEBUTTONDOWN) input->AddMouseButton(event.button.button);

		if (event.type == SDL_MOUSEBUTTONUP) input->RemoveMouseButton(event.button.button);
	}

	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	input->SetMousePosition(Vector2(mouseX, mouseY));

	if (input->GetKeyUp(Input::KeyCode::Escape)) isRunning = false;
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);	//Set the background colour
	SDL_RenderClear(renderer);							//Clear the render view

	//The render manager renders all objects in the game (if they've been added)
	renderManager->Render(renderer);

	for (int i = 0; i < m_NumPipes; i++) {
		pipes[i]->Render(renderer);
	}

	player->Render(renderer);

	//camera->Render(renderer);

	SDL_RenderPresent(renderer);						//Render the frame
}

//This function is called when the game exits
void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned.\n";
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