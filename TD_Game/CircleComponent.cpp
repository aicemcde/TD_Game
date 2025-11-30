#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
	:Component(owner)
	,mRadius(0.0f)
{
	SDL_Log("Debug: CircleComponent Created. Address: %p, Owner Arg: %p, mOwner Val: %p\n",
		this, owner, GetOwner());
}

Vector2 CircleComponent::GetCenter() const
{
	SDL_assert(mOwner != nullptr);
	return mOwner->GetPos();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();
	float radiSq = a.GetRadius() + b.GetRadius();
	radiSq *= radiSq;
	return distSq <= radiSq;
}