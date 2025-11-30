#pragma once
#include "Component.h"
#include "Graph_Types.h"
#include "Math.h"

class MouseInputComponent : public Component
{
public:
	MouseInputComponent(class Actor* owner, const TileMapData& map);
	void ProcessInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;
	
	void SetMap(const TileMapData& map) { mTileMap = map; }
	const TileMapData& GetMap() const { return mTileMap; }
private:
	bool IsValidIndex(int x, int y);
	Vector2 mMousePos;
	bool mIsDownMouse = false;
	TileMapData mTileMap;
	std::vector<Data> mBaseTilesForTurret;
	int mLastIndexX = -1;
	int mLastIndexY = -1;
};