#include "Game.h"
#include "Scene.h"
#include "ResourceManger.h"
#include "Enemy.h"
#include "BGActor.h"
#include <algorithm>

Game* Game::sInstance = nullptr;

Game::Game()
	:mWindow(nullptr)
	, mIsRunning(true)
	, mRenderer(nullptr)
	, mScene(nullptr)
	, mTicksCount(0)
{
	if (sInstance == nullptr) sInstance = this;
	mScreenSize = Vector2(1024.0f, 768.0f);
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

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("画像を読み込めません : %s", SDL_GetError());
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

	TmpGame(deltaTime);

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
	std::unique_ptr<BGActor> bgActor = std::make_unique<BGActor>(this);

	if (!mLevel.startNode || !mLevel.goalNode)
	{
		SDL_Log("start goal not exist");
		Shutdown();
		return;
	}

	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(this);
	enemy->Initialize(mLevel);
	mEnemies.emplace_back(enemy.get());

	mScene->AddActor(std::move(enemy));
	mScene->AddActor(std::move(bgActor));
}

void Game::UnloadData()
{
	mScene->Unload();
}

void Game::RemoveEnemy(Enemy* enemy)
{
	auto iter = std::find(mEnemies.begin(), mEnemies.end(), enemy);
	if (iter != mEnemies.end())
	{
		std::iter_swap(iter, mEnemies.end() - 1);
		mEnemies.pop_back();
	}
}

void Game::TmpGame(float deltaTime)
{
	cooldown -= deltaTime;
	if (cooldown < 0 && enemyCount < tmpEnemyNum)
	{
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(this);
		enemy->Initialize(mLevel);
		mEnemies.emplace_back(enemy.get());
		mScene->AddActor(std::move(enemy));
		++enemyCount;
		cooldown = tmpEnemyCooldown;
	}
	if (enemyCount == tmpEnemyNum && mEnemies.empty())
	{
		Shutdown();
		return;
	}
}