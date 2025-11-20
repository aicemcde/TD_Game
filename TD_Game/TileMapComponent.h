#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
#include <string>
#include <unordered_map>

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int updateOrder = 20);
	void Update(float deltaTIme) override;
	void Draw(SDL_Renderer* renderer) override;
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	
	void LoadCSV(const std::string& fileName);
	std::vector<std::vector<int>> GetTileMap() const { return mTileMap; }
	void SetTileTexture(int tileID, SDL_Texture* texture) { mTileTextures[tileID] = texture; }

private:
	Vector2 mScreenSize;
	std::vector<std::vector<int>> mTileMap; //çsxóÒ
	std::unordered_map<int, SDL_Texture*> mTileTextures;
};