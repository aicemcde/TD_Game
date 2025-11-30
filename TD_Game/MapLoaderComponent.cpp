#include "MapLoaderComponent.h"
#include "SDL.h"
#include <fstream>
#include <sstream>
#include "Game.h"

const float STRAIGHT_COST = 1.0f;	//直線移動コスト(Weight)

MapLoaderComponent::MapLoaderComponent(Actor* owner, const std::string& fileName)
	: Component(owner)
{
	LoadCSV(fileName);
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
		std::vector<Data> addTilesRow;
		std::string tileStr;
		std::istringstream iss(tilesRowStr);

		while (std::getline(iss, tileStr, ','))
		{
			int tile = std::stoi(tileStr);
			Data addTile;
			addTile.mTileType = tile;
			addTilesRow.emplace_back(addTile);
		}

		mTileMap.emplace_back(addTilesRow);
	}

	Vector2 screenSize = Game::Get().GetScreenSize();
	int height = static_cast<int>(mTileMap.size());
	int width = static_cast<int>(mTileMap[0].size());

	float tileSize_x = screenSize.x / width;
	float tileSize_y = screenSize.y / height;
	mTileSize = Vector2(tileSize_x, tileSize_y);
	Game::Get().SetTileSize(mTileSize);
}

GameLevel MapLoaderComponent::BuildGraphFromGrid()
{
	GameLevel level;
	int height = static_cast<int>(mTileMap.size());
	if (height == 0) return level;
	int width = static_cast<int>(mTileMap[0].size());

	SDL_Log("BuildGraphFromGrid: width=%d, height=%d, tileSize=(%.1f, %.1f)", width, height, mTileSize.x, mTileSize.y);
	NodeGrid nodeGrid(height, std::vector<WeightedGraphNode*>(width, nullptr));

	GenerateNodes(height, width, mTileSize, &level, &nodeGrid);

	//隣接ノードの設定
	ConnectEdges(height, width, nodeGrid);
	return level;
}

void MapLoaderComponent::GenerateNodes(const int height, const int width, const Vector2& tileSize, GameLevel* outLevel, NodeGrid* outNodeGrid)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float posX = static_cast<float>(x * tileSize.x + tileSize.x * 0.5f);
			float posY = static_cast<float>(y * tileSize.y + tileSize.y * 0.5f);
			mTileMap[y][x].mCenterPos = Vector2(posX, posY);

			int tileType = mTileMap[y][x].mTileType;
			if (tileType != TileTypes::NONE && tileType != TileTypes::NORMALGROUND)
			{
				std::unique_ptr<WeightedGraphNode> newNode = std::make_unique<WeightedGraphNode>();
				newNode->mPos = Vector2(posX, posY);
				
				WeightedGraphNode* rawNodePtr = newNode.get();

				if (tileType == TileTypes::START) outLevel->startNode = rawNodePtr;
				else if (tileType == TileTypes::GOAL) outLevel->goalNode = rawNodePtr;
				(*outNodeGrid)[y][x] = rawNodePtr;
				outLevel->graph.mNodes.emplace_back(std::move(newNode));
			}
		}
	}
}

void MapLoaderComponent::ConnectEdges(const int height, const int width, const NodeGrid& nodeGrid)
{
	int dirX[] = { 0,0, -1, 1 };
	int dirY[] = { -1,1, 0, 0 };

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			WeightedGraphNode* currentNode = nodeGrid[y][x];
			if (currentNode == nullptr) continue;

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
						edge.mWeight = STRAIGHT_COST;
						currentNode->mEdges.emplace_back(edge);
					}
				}
			}
		}
	}
}