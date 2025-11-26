#pragma once
#include "Component.h"
#include "Graph_Types.h"
#include "Math.h"

class MouseInputComponent : public Component
{
public:
	MouseInputComponent(class Actor* owner);
	void ProcessInput(const uint8_t* keyState) override;
	void Initialize(const GridData& map);

	void SetMap(const GridData& map) { mTileMap = map; }
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	const GridData& GetMap() const { return mTileMap; }
private:
	GridData mTileMap;
	Vector2 mScreenSize = Vector2::Zero;
	Vector2 mTileSize = Vector2::Zero;
	std::vector<Vector2> mCanBuildTurretPoss;	//タレットを設置できる座標配列
	std::vector<Vector2> mPossForMap;	//上の座標のマップ上の座標配列, Vector2(列, 行)
};