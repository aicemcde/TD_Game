#pragma once
#include "Graph_Types.h"

namespace PathFinding
{
	std::vector<const WeightedGraphNode*> AStarSearch(const GameLevel& level);

	float ComputeHeuristic(const WeightedGraphNode* mTo, const WeightedGraphNode* goalNode);
}