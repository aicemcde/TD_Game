#pragma once
#include "AIState.h"

class AIShot : public AIState
{
public:
	AIShot(class AIComponent* owner);

	void OnEnter() override;
	void OnExit() override;
	void Update(float deltaTime) override;
	const char* GetName() const override { return "Shot"; }
};