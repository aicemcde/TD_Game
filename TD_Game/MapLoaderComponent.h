#pragma once
#include "Component.h"
#include <string>

class MapLoaderComponent : public Component
{
public:
	MapLoaderComponent(class Actor* owner, const std::string& fileName);
	GameLevel BuildGraphFromGrid();
	TileMapData GetMap() const { return mTileMap; }
private:
	using NodeGrid = std::vector<std::vector<WeightedGraphNode*>>;

	void LoadCSV(const std::string& fileName);
	void GenerateNodes(const int height, const int width, const Vector2& tileSize, GameLevel* outLevel, NodeGrid* outNodeGrid);
	void ConnectEdges(const int height, const int width, const NodeGrid& nodeGrid);

	TileMapData mTileMap;
	Vector2 mTileSize;
};

