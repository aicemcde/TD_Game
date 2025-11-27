#pragma once
#include "Actor.h"

class Game;

class Turret : public Actor
{
public:
	Turret(class Game* game, const Vector2& centerPos);

	void UpdateActor(float deltaTime) override;
private:
	class SpriteComponent* mSprComp = nullptr;
	class AIComponent* mAIComp = nullptr;

	float mMissileCooldown = 1.0f;
};