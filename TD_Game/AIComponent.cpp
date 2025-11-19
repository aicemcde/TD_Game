#include "AIComponent.h"
#include "AIState.h"
#include <SDL.h>

AIComponent::AIComponent(class Actor* owner)
	:Component(owner)
	,mCurrentState(nullptr)
{
}

void AIComponent::Update(float deltaTime)
{
	if (mCurrentState)
	{
		mCurrentState->Update(deltaTime);
	}
}

void AIComponent::RegisterState(std::unique_ptr<AIState> state)
{
	mStateMap.emplace(state->GetName(), std::move(state));
}

void AIComponent::ChangeState(const std::string& name)
{
	if (mCurrentState)
	{
		mCurrentState->OnExit();
	}

	auto iter = mStateMap.find(name);
	if (iter != mStateMap.end())
	{
		mCurrentState = iter->second;
		mCurrentState->OnEnter();
	}
	else
	{
		SDL_Log("AIState %s ‚Ìó‘Ô‚Í‚ ‚è‚Ü‚¹‚ñ", name.c_str());
		mCurrentState = nullptr;
	}
}