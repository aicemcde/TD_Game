#pragma once
#include "Actor.h"

class Missile : public Actor
{
public:
	Missile(class Game* owner, class Enemy* enemy, const Vector2& pos);
	void UpdateActor(float deltaTime) override;
private:
	class CircleComponent* mCircle = nullptr;
	class Enemy* mTargetEnemy = nullptr;
};