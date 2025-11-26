#pragma once
#include "Graph_Types.h"
#include "Component.h"
#include <string>

class MapLoaderComponent : public Component
{
public:
	MapLoaderComponent(class Actor* owner);
	GameLevel BuildGraphFromGrid(const Vector2& screen);

	void LoadCSV(const std::string& fileName);
	std::vector<std::vector<int>> GetMap() const { return mTileMap; }
private:
	GridData mTileMap;
};

