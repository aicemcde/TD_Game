#pragma once
#include <vector>
#include "Math.h"

using GridData = std::vector<std::vector<int>>;

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
	void SetPos(const Vector2& pos) { mPos = pos; }
	Vector2 GetPos() const { return mPos; }
};

struct WeightedGraph
{
	std::vector<WeightedGraphNode> mNodes;
};

struct GraphNode
{
	std::vector<struct GraphNode*> mAdjacentNodes;
};

struct Graph
{
	std::vector<GraphNode> mNodes;
};

struct GameLevel
{
	WeightedGraph graph;
	WeightedGraphNode* startNode = nullptr;
	WeightedGraphNode* goalNode = nullptr;
};