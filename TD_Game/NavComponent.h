#pragma once
#include "MoveComponent.h"
#include "Math.h"
#include "A-Star_Search.h"

class NavComponent : public MoveComponent
{
public:
	NavComponent(class Actor* owner, int updateOrder = 10);
	void Update(float delta) override;
	void TurnTo(const Vector2& pos);
	void GetNextPos();
	void SetPath();
private:
	Vector2 mNextPos;
	std::vector<WeightedGraphNode*> mPath;
	std::vector<Vector2> mWayPoints;
};
