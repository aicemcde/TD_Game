#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game)
	:mState(EActive)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
	,mGame(game)
{
	
}

Actor::~Actor()
{
	
}

void Actor::Update(float deltaTime)
{
	UpdateComponents(deltaTime);
	UpdateActor(deltaTime);
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto& comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
	
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		for (auto& comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{

}

void Actor::AddComponent(std::unique_ptr<class Component> comp)
{
	const int myOrder = comp->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, std::move(comp));
}

void Actor::RemoveComponent(class Component* comp)
{
	auto iter = std::find_if(mComponents.begin(), mComponents.end(),
		[comp](const std::unique_ptr<Component>& ptr)
		{
			return ptr.get() == comp;
		}
	);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}