#include "A-Star_Search.h"
#include <unordered_map>
#include <cmath>

namespace PathFinding
{
	struct AStarScratch
	{
		const WeightedEdge* mParentEdge = nullptr;	//経路復元用
		float mHeuristicCost = 0.0f;
		float mActualFromStartCost = 0.0f;
		bool mInOpenSet = false;
		bool mInClosedSet = false;
	};

	using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;

	std::vector<const WeightedGraphNode*> AStarSearch(
		const WeightedGraphNode* startNode, 
		const WeightedGraphNode* goalNode)
	{
		AStarMap nodeMap;//各ノードごとの情報

		std::vector<const WeightedGraphNode*> openSet;

		nodeMap[startNode].mInClosedSet = true;
		nodeMap[startNode].mHeuristicCost = ComputeHeuristic(startNode, goalNode);
		nodeMap[startNode].mActualFromStartCost = 0.0f;
		openSet.emplace_back(startNode);

		while (!openSet.empty())
		{
			//評価
			auto iter = std::min_element(
				openSet.begin(),
				openSet.end(),
				[&nodeMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
				{
					float fa = nodeMap[a].mHeuristicCost + nodeMap[a].mActualFromStartCost;
					float fb = nodeMap[b].mHeuristicCost + nodeMap[b].mActualFromStartCost;
					return fa < fb;
				}
			);

			const WeightedGraphNode* currentNode = *iter;

			if (currentNode == goalNode)
			{
				break;
			}
			openSet.erase(iter);
			nodeMap[currentNode].mInOpenSet = false;
			nodeMap[currentNode].mInClosedSet = true;

			//currの隣のノードを調査
			for (const WeightedEdge& edge : currentNode->mEdges)
			{
				const WeightedGraphNode* neighbor = edge.mTo;
				AStarScratch& data = nodeMap[neighbor];
				if (data.mInClosedSet)
				{
					continue;
				}

				float newG = nodeMap[currentNode].mActualFromStartCost + edge.mWeight;

				if (!data.mInOpenSet || newG < data.mActualFromStartCost)
				{
					data.mActualFromStartCost = newG;
					data.mHeuristicCost = ComputeHeuristic(neighbor, goalNode);
					data.mParentEdge = &edge;
					if (!data.mInOpenSet)
					{
						data.mInOpenSet = true;
						openSet.emplace_back(neighbor);
					}
				}
			}

			if (nodeMap.find(goalNode) == nodeMap.end() || !nodeMap[goalNode].mParentEdge)
			{
				if (startNode == goalNode)
				{
					return { startNode };
				}
				return {};
			}

			//経路の復元
			std::vector<const WeightedGraphNode*> path;
			const WeightedGraphNode* curr = goalNode;
			while (curr != startNode || curr != nullptr)
			{
				path.emplace_back(curr);
				const WeightedEdge* parentEdge = nodeMap[curr].mParentEdge;		//親のエッジ(線)を取得
				curr = parentEdge->mFrom;										//親ノードに移動
			}

			path.emplace_back(startNode);
			std::reverse(path.begin(), path.end());

			return path;
		}
	}

	float ComputeHeuristic(const WeightedGraphNode* mTo, const WeightedGraphNode* goalNode)
	{
		Vector2 diff = goalNode->GetPos() - mTo->GetPos();
		return diff.Length();
	}
}

