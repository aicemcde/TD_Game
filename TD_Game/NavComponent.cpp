#include "NavComponent.h"
#include "Actor.h"
#include "A-Star_Search.h"

NavComponent::NavComponent(class Actor* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
{
}

void NavComponent::Update(float delta)
{

	if (mCurrentWayPoint >= mNumWayPoints || mWayPointsPos.empty())
	{
		SDL_Log("NavComponent: no waypoints or operaton end");
		return;
	}
	Vector2 diff = mOwner->GetPos() - mNextPos;
	if (diff.LengthSq() <= 2.0f * 2.0f)
	{
		++mCurrentWayPoint;
		if (mCurrentWayPoint < mNumWayPoints - 1)
		{
			mNextPos = mWayPointsPos.at(mCurrentWayPoint + 1);
			TurnTo(mNextPos);
		}
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
	mWayPointsPos.clear();

	if (mPath.empty())
	{
		SDL_Log("path not find");
		return;
	}

	for (auto& node : mPath)
	{
		mWayPointsPos.emplace_back(node->GetPos());
	}

	mNumWayPoints = static_cast<int>(mWayPointsPos.size());

	if (mNumWayPoints > 0)
	{
		
		mNextPos = mWayPointsPos.at(0);
		mCurrentWayPoint = -1;
		
	}
	else
	{
		SDL_Log("SetPath : waypoints pos empty");
	}
}

Vector2 NavComponent::GetFirstPos()
{
	if (!mWayPointsPos.empty())
	{
		return mWayPointsPos.at(0);
	}
	return Vector2::Zero;
}