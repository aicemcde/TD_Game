#pragma once
#include <memory>
#include <vector>
#include <SDL.h>

class Scene
{
public:
	Scene(class Game* game);
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer);
	void Unload();

	void AddActor(std::unique_ptr<class Actor> actor);
	void RemoveActor(class Actor* actor);

	void AddSpriteComponent(class SpriteComponent* sc);
	void RemoveSpriteComponent(class SpriteComponent* sc);

private:
	std::vector<std::unique_ptr<class Actor>> mActors;
	std::vector<std::unique_ptr<class Actor>> mPendingActors;
	class Game* mGame;
	bool mUpdatingActors;

	std::vector<class SpriteComponent*> mSpriteComps;
};