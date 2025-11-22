#include "MapLoaderComponent.h"
#include "SDL.h"
#include <fstream>
#include <sstream>

const int TILE_SIZE = 64;
const float STRIGHT_COST = 1.0f;	//直線移動コスト(Weight)

MapLoaderComponent::MapLoaderComponent(Actor* owner)
	: Component(owner)
{
}

void MapLoaderComponent::LoadCSV(const std::string& fileName)
{
	std::ifstream tileMap(fileName);

	if (!tileMap)
	{
		SDL_Log("Failed to open tile map file: %s", fileName.c_str());
		return;
	}

	std::string tilesRowStr;
	while (std::getline(tileMap, tilesRowStr))
	{
		std::vector<int> addTilesRow;
		std::string tileStr;
		std::istringstream iss(tilesRowStr);

		while (std::getline(iss, tileStr, ','))
		{
			int tile = std::stoi(tileStr);
			addTilesRow.emplace_back(tile);
		}

		mTileMap.emplace_back(addTilesRow);
	}
}

GameLevel MapLoaderComponent::BuildGraphFromGrid(const Vector2& screenSize)
{
	GameLevel level;
	int height = static_cast<int>(mTileMap.size());
	if (height == 0)
	{
		return level;
	}
	int width = static_cast<int>(mTileMap[0].size());

	int tileSize_x = static_cast<int>(screenSize.x) / width;
	int tileSize_y = static_cast<int>(screenSize.y) / height;
	SDL_Log("BuildGraphFromGrid: width=%d, height=%d, tileSize=(%d, %d)", width, height, tileSize_x, tileSize_y);
	std::vector<std::vector<WeightedGraphNode*>> nodeGrid(height, std::vector<WeightedGraphNode*>(width, nullptr));

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int tileType = mTileMap[y][x];
			if (tileType != -1 && tileType != 1)
			{
				WeightedGraphNode* newNode = new WeightedGraphNode();
				float posX = static_cast<float>(x * tileSize_x + tileSize_x * 0.5f);	
				float posY = static_cast<float>(y * tileSize_y + tileSize_y * 0.5f);
				newNode->SetPos(Vector2(posX, posY));
				SDL_Log("Node created at (%.1f, %.1f) for tileType %d", posX, posY, tileType);

				if (tileType == 100)
				{
					level.startNode = newNode;
				}
				else if (tileType == 200)
				{
					level.goalNode = newNode;
				}

				level.graph.mNodes.emplace_back(*newNode);
				nodeGrid[y][x] = newNode;
			}
		}
	}

	//隣接ノードの設定
	int dirX[] = { 0,0, -1, 1 };
	int dirY[] = { -1,1, 0, 0 };

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			WeightedGraphNode* currentNode = nodeGrid[y][x];
			if (currentNode == nullptr)
			{
				continue;
			}

			for (int i = 0; i < 4; ++i)
			{
				int nx = x + dirX[i];
				int ny = y + dirY[i];

				if (nx >= 0 && nx < width && ny >= 0 && ny < height)
				{
					WeightedGraphNode* neighborNode = nodeGrid[ny][nx];
					if (neighborNode != nullptr)
					{
						WeightedEdge edge;
						edge.mFrom = currentNode;
						edge.mTo = neighborNode;
						edge.mWeight = STRIGHT_COST;
						currentNode->mEdges.emplace_back(edge);
					}
				}
			}
		}
	}
	return level;
}