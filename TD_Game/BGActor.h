#pragma once
#include "Actor.h"
#include "Graph_Types.h"

class BGActor : public Actor
{
public:
	BGActor(class Game* game);
	void UpdateActor(float deltaTime) override;

	void GenerateTurret();

	const GameLevel& GetLevel() const { return mLevel; }
private:
	class MouseInputComponent* mMIComp = nullptr;
	class TileMapComponent* mTMComp = nullptr;
	GridData mTileMap;
	Vector2 mScreenSize = Vector2(1024.0f, 768.0f);
	GameLevel mLevel;
};