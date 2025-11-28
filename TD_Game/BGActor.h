#pragma once
#include "Actor.h"
#include "Graph_Types.h"

class BGActor : public Actor
{
public:
	BGActor(class Game* game);
	void UpdateActor(float deltaTime) override;
private:
	class MouseInputComponent* mMIComp = nullptr;
	class TileMapComponent* mTMComp = nullptr;
	GameLevel mLevel;
	TileDatas mTileMap;
};