#include "A-Star_Search.h"
#include <unordered_map>
#include <cmath>
#include <SDL.h>

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

	std::vector<const WeightedGraphNode*> AStarSearch(const GameLevel& level)
	{
		AStarMap nodeMap;		//各ノードごとの情報

		std::vector<const WeightedGraphNode*> openSet;

		const WeightedGraphNode* startNode = level.startNode;
		const WeightedGraphNode* goalNode = level.goalNode;

		if (!startNode || !goalNode)
		{
			SDL_Log("start or goal not exist");
			return {};
		}

		nodeMap[startNode].mInOpenSet = true;
		nodeMap[startNode].mInClosedSet = false;
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

			
			openSet.erase(iter);
			nodeMap[currentNode].mInOpenSet = false;
			nodeMap[currentNode].mInClosedSet = true;

			//経路の復元
			if (currentNode == goalNode)
			{
				std::vector<const WeightedGraphNode*> path;
				const WeightedGraphNode* curr = goalNode;
				while (curr != startNode && curr != nullptr)
				{
					path.emplace_back(curr);
					const WeightedEdge* parentEdge = nodeMap[curr].mParentEdge;		//親のエッジ(線)を取得
					if (parentEdge)
					{
						curr = parentEdge->mFrom;		//親ノードに移動
					}
					else
					{
						break;
					}
																
				}

				std::reverse(path.begin(), path.end());
				return path;
			}

			//隣のノードを調査
			for (const WeightedEdge& edge : currentNode->mEdges)
			{
				const WeightedGraphNode* neighbor = edge.mTo;
				AStarScratch& data = nodeMap[neighbor];
				if (data.mInClosedSet)
				{
					continue;
				}

				float newG = nodeMap[currentNode].mActualFromStartCost + edge.mWeight;

				//オープンセットにない、またはより良い経路が見つかった場合、情報を更新
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

		}

		// ループを抜けた場合、経路が見つからなかったので空のパスを返す
		SDL_Log("goal not reached");
		return {};
	}

	float ComputeHeuristic(const WeightedGraphNode* mFrom, const WeightedGraphNode* goalNode)
	{
		Vector2 diff = goalNode->mPos - mFrom->mPos;
		return diff.Length();
	}
}

