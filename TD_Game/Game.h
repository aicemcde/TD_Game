#pragma once
#include <SDL.h>
#include <memory>
#include "Graph_Types.h"

class Scene;
class ResourceManager;

class Game
{
public:
	Game();
	~Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	class Scene* GetScene()  { return mScene.get(); }
	class ResourceManager* GetResourceManager() const { return mResourceManager.get(); }
	SDL_Renderer* GetRenderer() const { return mRenderer; }

	void SetMissile(class Missile* missile) { mMissiles.emplace_back(missile); }

	static Game& Get() { return *sInstance; }
	const Vector2& GetScreenSize() { return mScreenSize; }
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	const Vector2& GetTileSize() { return mTileSize; }
	void SetTileSize(const Vector2& size) { mTileSize = size; }
	const GameLevel& GetLevel() const { return mLevel; }
	void SetLevel(GameLevel level) { mLevel = std::move(level); }
	const std::vector<class Enemy*>& GetEnemies() const { return mEnemies; }

	void RemoveEnemy(class Enemy* enemy);

	void TmpGame(float deltaTime);
private:
	static Game* sInstance;
	Vector2 mScreenSize;
	Vector2 mTileSize;
	GameLevel mLevel;

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	SDL_Window* mWindow;
	bool mIsRunning;
	SDL_Renderer* mRenderer;

	Uint32 mTicksCount;

	std::unique_ptr<class Scene> mScene;
	std::unique_ptr<class ResourceManager> mResourceManager;

	std::vector<class Enemy*> mEnemies;
	std::vector<class Missile*> mMissiles;

	const int tmpEnemyNum = 10;
	const float tmpEnemyCooldown = 3.00f;
	float cooldown = tmpEnemyCooldown;
	int enemyCount = 1;
};