#include "NavComponent.h"
#include "Actor.h"


NavComponent::NavComponent(class Actor* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
{
}

void NavComponent::Update(float delta)
{
	Vector2 diff = mOwner->GetPos() - mNextPos;
	if (diff.Length() < 2.0f)
	{

	}
	MoveComponent::Update(delta);
}

void NavComponent::TurnTo(const Vector2& pos)
{
	Vector2 dir = pos - mOwner->GetPos();
	float angle = Math::Atan2(-dir.y, dir.x);
	mOwner->SetRot(angle);
}

void NavComponent::SetPath()
{
	
}