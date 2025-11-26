#pragma once
#include "Actor.h"

class Missile : public Actor
{
public:
	Missile(class Game* owner);

private:
	class CircleComponent* mCircle = nullptr;
};