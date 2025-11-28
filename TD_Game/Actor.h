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
	Vector2 GetPos() const { return mCenterPosition; }
	float GetScale() const { return mScale; }
	float GetRot() const { return mRotation; }
	void SetState(const State& state) { mState = state; }
	void SetPos(const Vector2& pos) { mCenterPosition = pos; }
	void SetScale(float scale) { mScale = scale; }
	void SetRot(float rot) { mRotation = rot; }

	Game* GetGame() const { return mGame; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	void AddComponent(std::unique_ptr<class Component> comp);
	void RemoveComponent(class Component* comp);
protected:
	State mState;
	Vector2 mCenterPosition;
	float mScale;
	float mRotation;
	std::vector < std::unique_ptr<class Component>> mComponents;
	class Game* mGame;
};