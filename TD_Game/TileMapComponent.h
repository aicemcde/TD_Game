#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
#include <unordered_map>
#include "Graph_Types.h"

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTIme) override;
	void Draw(SDL_Renderer* renderer) override;
	void SetTileMap(const TileMapData& tileMap) { mTileMap = tileMap; }
	
	TileMapData GetTileMap() const { return mTileMap; }
	void SetTileTexture(int tileID, SDL_Texture* texture) { mTileTextures[tileID] = texture; }

private:
	TileMapData mTileMap;
	std::unordered_map<int, SDL_Texture*> mTileTextures;
};