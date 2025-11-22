#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mForwardSpeed(0.0f)
	,mAngularSpeed(0.0f)
{
}

void MoveComponent::Update(float delta)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRot();
		rot += mAngularSpeed * delta;
		mOwner->SetRot(rot);
	}
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPos();
		pos += mOwner->GetForward() * mForwardSpeed * delta;
		mOwner->SetPos(pos);
	}
}