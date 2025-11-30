#pragma once
#include <vector>
#include "Math.h"
#include <memory>

using GridData = std::vector<std::vector<int>>;

struct Data	//一マスごとの情報
{
	Vector2 mCenterPos = Vector2::Zero;
	bool mHadTurret = false;
	int mTileType = -1;
};

using TileMapData = std::vector<std::vector<Data>>;

struct WeightedGraphNode;

struct WeightedEdge
{
	struct WeightedGraphNode* mFrom = nullptr;
	struct WeightedGraphNode* mTo = nullptr;

	float mWeight = 1.0f;
};

struct WeightedGraphNode
{
	std::vector<WeightedEdge> mEdges;
	Vector2 mPos;
};

struct WeightedGraph
{
	std::vector<std::unique_ptr<WeightedGraphNode>> mNodes;
};

struct GameLevel	//ここでのlevelはマップ、面等の意味
{
	WeightedGraph graph;
	WeightedGraphNode* startNode = nullptr;
	WeightedGraphNode* goalNode = nullptr;
};

enum TileTypes
{
	NONE = -1,
	NORMALGROUND = 1,
	SELECTEDNORMALGROUND = 11,
	LOAD = 2,
	START = 100,
	GOAL = 200,
	TURRETBASEGROUND = 22
};