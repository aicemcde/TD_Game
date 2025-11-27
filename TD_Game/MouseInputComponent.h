#pragma once
#include "Component.h"
#include "Graph_Types.h"
#include "Math.h"

class MouseInputComponent : public Component
{
public:
	MouseInputComponent(class Actor* owner, const TileDatas& map);
	void ProcessInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;
	
	void SetMap(const TileDatas& map) { mTileMap = map; }
	const TileDatas& GetMap() const { return mTileMap; }
private:
	bool IsValidIndex(int x, int y);
	Vector2 mMousePos;
	bool mIsDownMouse = false;
	TileDatas mTileMap;
	std::vector<Data> mBaseTilesForTurret;
	int mLastIndexX = -1;
	int mLastIndexY = -1;
};