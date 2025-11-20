#include "NavComponent.h"
#include "Actor.h"
#include "A-Star_Search.h"

NavComponent::NavComponent(class Actor* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
{
}

void NavComponent::Update(float delta)
{
	Vector2 diff = mOwner->GetPos() - mNextPos;
	if (diff.Length() < 2.0f)
	{
		mNextPos = mWayPointsPos[mCurrentWayPoint];
		TurnTo(mNextPos);
		mCurrentWayPoint++;
	}
	MoveComponent::Update(delta);
}

void NavComponent::TurnTo(const Vector2& pos)
{
	Vector2 dir = pos - mOwner->GetPos();
	float angle = Math::Atan2(-dir.y, dir.x);
	mOwner->SetRot(angle);
}

void NavComponent::SetPath(const GameLevel& level)
{
	mPath = PathFinding::AStarSearch(level);
	if (mPath.empty())
	{
		SDL_Log("path not find");
		return;
	}
	mNumWayPoints = static_cast<int>(mPath.size());
	for (auto& node : mPath)
	{
		mWayPointsPos.emplace_back(node->GetPos());
	}

}