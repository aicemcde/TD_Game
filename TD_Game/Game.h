#pragma once
#include <SDL.h>
#include <memory>
#include <vector>

class Game
{
public:
	Game();
	~Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();
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
};