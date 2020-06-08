#include "PipeObject.h"
#include "Time.h"

PipeObject::PipeObject()
{
	m_BottomDest = m_TopDest = m_TopSource = m_BottomSource = { 0, 0, 0, 0 };
	m_BottomSprite = m_TopSprite = 0;
}

PipeObject::~PipeObject()
{
	delete m_BottomSprite;
	delete m_TopSprite;
	m_TopSprite = m_BottomSprite = 0;
}

void PipeObject::Initialise(SDL_Renderer* renderer, Vector2 position, Vector2 size)
{
	m_Pos = position;
	m_Size = size;

	m_TopBox.Initialise(position, Vector2(0, m_Size.y / 4 + 1.25f), Vector2(size.x * 0.8f, size.y / 2));
	m_BottomBox.Initialise(position, Vector2(0, -m_Size.y / 4 - 1.25f), Vector2(size.x * 0.8f, size.y / 2));

	m_BottomSprite = new SpriteRenderer();
	m_TopSprite = new SpriteRenderer();
	spritePath = "Assets/Flappy_Bird_Spritesheet.png";

	m_TopDest.x = m_Pos.x - (m_Size.x / 2);
	m_TopDest.y = m_Pos.y - m_Size.y * 2;
	m_TopDest.w = m_Size.x;
	m_TopDest.h = m_Size.y / 2;

	m_BottomDest.x = m_Pos.x - (m_Size.x / 2);
	m_BottomDest.y = m_Pos.y + m_Size.y * 2;
	m_BottomDest.w = m_Size.x;
	m_BottomDest.h = m_Size.y / 2;

	m_TopSource = SDL_Rect{ 54, 323, 30, 160 };
	m_BottomSource = SDL_Rect{ 82, 323, 30, 160 };

	m_TopSprite->Initialise(spritePath, renderer, m_TopSource);
	m_BottomSprite->Initialise(spritePath, renderer, m_BottomSource);
}

void PipeObject::Update()
{
	m_TopSprite->renderSprite = true;
	m_BottomSprite->renderSprite = true;

	m_Pos.x -= 2.5 * Time::GetDeltaTime();

	m_TopBox.position = m_BottomBox.position = m_Pos;
	m_TopBox.Update();
	m_BottomBox.Update();

	RenderManager::Instance->AddToRenderQueue(m_TopSprite, Vector2(m_Pos.x, (m_Pos.y + m_Size.y / 4) + 1.25), Vector2(m_Size.x, m_Size.y / 2));
	RenderManager::Instance->AddToRenderQueue(m_BottomSprite, Vector2(m_Pos.x, (m_Pos.y - m_Size.y / 4) - 1.25), Vector2(m_Size.x, m_Size.y / 2));
}

void PipeObject::Render(SDL_Renderer* renderer) {
	m_TopBox.Render(renderer, SDL_Color{ 0, 255, 0, 255 });
	m_BottomBox.Render(renderer, SDL_Color{ 0, 255, 0, 255 });
}

void PipeObject::SetPosition(Vector2 position)
{
	m_Pos = position;
}
