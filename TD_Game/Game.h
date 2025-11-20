#pragma once
#include <SDL.h>
#include <memory>
#include "Graph_Types.h"

class Game
{
public:
	Game();
	~Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	class Scene* GetScene() const { return mScene.get(); }
	class ResourceManager* GetResourceManager() const { return mResourceManager.get(); }
	SDL_Renderer* GetRenderer() const { return mRenderer; }
private:
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

	GameLevel level;
};