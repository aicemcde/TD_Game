#pragma once
#include "AIState.h"

class AIDeath : public AIState
{
public:
	AIDeath(class AIComponent* owner);
	
	void Update(float deltaTime) override;
	void OnEnter() override;

	const char* GetName() const override { return "Death"; }
};