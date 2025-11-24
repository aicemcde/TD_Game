#pragma once
#include "AIState.h"

class AIMove : public AIState
{
public:
	AIMove(class AIComponent* owner);

	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;
	
	const char* GetName() const override { return "Move"; }
};