#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
	:Component(owner)
	,mRadius(0.0f)
{

}

const Vector2& CircleComponent::GetCenter() const
{
	const Vector2& pos = mOwner->GetPos();
	return pos;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();
	float radiSq = a.GetRadius() - b.GetRadius();
	radiSq *= radiSq;
	return distSq <= radiSq;
}