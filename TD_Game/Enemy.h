#pragma once
#include "Actor.h"
#include "Graph_Types.h"

class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	void Initialize(const GameLevel& level);
	void UpdateActor(float deltaTime) override;
	class SpriteComponent* GetSprite() const { return mSprComp; }
	class CircleComponent* GetCircle() const { return mCComp; }
	class AIComponent* GetAI() const { return mAIComp; }
private:
	class NavComponent* mNavComp = nullptr;
	class SpriteComponent* mSprComp = nullptr;
	class AIComponent* mAIComp = nullptr;
	class CircleComponent* mCComp = nullptr;
};