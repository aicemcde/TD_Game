#pragma once
#include "Graph_Types.h"

namespace PathFinding
{
	std::vector<const WeightedGraphNode*> AStarSearch(
		const WeightedGraphNode* startNode, 
		const WeightedGraphNode* goalNode
	);

	float ComputeHeuristic(const WeightedGraphNode* mTo, const WeightedGraphNode* goalNode);
}