#pragma once
#include "MoveComponent.h"
#include "Math.h"
#include "Graph_Types.h"

class NavComponent : public MoveComponent
{
public:
	NavComponent(class Actor* owner, int updateOrder = 10);
	void Update(float delta) override;
	void TurnTo(const Vector2& pos);
	void SetPath(const GameLevel& level);
	Vector2 GetFirstPos() const { if (!mWayPointsPos.empty()) { return mWayPointsPos.at(0); } }
	bool HasHash() const { return !mWayPointsPos.empty(); }
private:
	Vector2 mNextPos;
	std::vector<const WeightedGraphNode*> mPath;	//経路上のノード
	std::vector<Vector2> mWayPointsPos;		//経路上の位置
	int mCurrentWayPoint = 0;				//現在の経路上の位置インデックス
	int mNumWayPoints = 0;					//経路上の位置数
};
