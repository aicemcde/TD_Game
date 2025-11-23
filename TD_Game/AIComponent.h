#pragma once
#include "Component.h"
#include <string>
#include <unordered_map>
#include <memory>

class AIComponent : public Component
{
public:
	AIComponent(class Actor* owner);

	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);

	void RegisterState(std::unique_ptr<class AIState> state);
private:
	std::unordered_map<std::string, std::unique_ptr<class AIState>> mStateMap;
	class AIState* mCurrentState;
};