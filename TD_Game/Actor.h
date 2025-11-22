#pragma once
#include <cstdint>
#include <memory>
#include "Math.h"
#include <vector>
#include "Game.h"

class Actor
{
public:
	enum State
	{
		EActive,
		EPouse,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	State GetState() const { return mState; }
	Vector2 GetPos() const { return mPosition; }
	float GetScale() const { return mScale; }
	float GetRot() const { return mRotation; }
	void SetState(const State& state) { mState = state; }
	void SetPos(const Vector2& pos) { mPosition = pos; }
	void SetScale(float scale) { mScale = scale; }
	void SetRot(float rot) { mRotation = rot; SDL_Log("SetRot : %.1f", rot); }

	Game* GetGame() const { return mGame; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	void AddComponent(std::unique_ptr<class Component> comp);
	void RemoveComponent(class Component* comp);
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	std::vector < std::unique_ptr<class Component>> mComponents;
	class Game* mGame;
};