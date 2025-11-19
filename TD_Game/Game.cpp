#include "Game.h"
#include "Actor.h"
#include <algorithm>
#include "Scene.h"
#include "ResourceManger.h"

Game::Game()
	:mWindow(nullptr)
	,mIsRunning(true)
	,mRenderer(nullptr)
	,mScene(nullptr)
	,mTicksCount(0)
{

}

Game::~Game()
{

}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("SDLを初期化できません : %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("TD_Game", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("ウィンドウを生成できません : %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("レンダラーを生成できません : %s", SDL_GetError());
		return false;
	}

	mTicksCount = SDL_GetTicks();

	mScene = std::make_unique<Scene>(this);
	mResourceManager = std::make_unique<ResourceManager>();

	LoadData();

	return true;
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		default:
			break;

		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	mScene->InputActor(keyState);
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	mScene->Update(deltaTime);
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	mScene->Draw(mRenderer);
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	
}

void Game::UnloadData()
{
	mScene->Unload();
}