#pragma once
#include "Actor.h"
#include "Graph_Types.h"

class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	void Initialize(const GameLevel& level);
	class SpriteComponent* GetSprite() const { return mSprComp; }
private:
	class NavComponent* mNavComp = nullptr;
	class SpriteComponent* mSprComp = nullptr;
};