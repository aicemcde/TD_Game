#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
	:Component(owner)
{

}

const Vector2& CircleComponent::GetCenter() const
{
	return mOwner->GetPos();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();
	float radiSq = a.GetRadius() - b.GetRadius();
	radiSq *= radiSq;
	return distSq <= radiSq;
}