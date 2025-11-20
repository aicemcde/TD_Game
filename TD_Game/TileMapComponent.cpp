#include "TileMapComponent.h"


TileMapComponent::TileMapComponent(Actor* owner, int updateOrder)
	: SpriteComponent(owner, updateOrder)
{
}

void TileMapComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
}



void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect;
	dstRect.w = static_cast<int>(mScreenSize.x / mTileMap[0].size());
	dstRect.h = static_cast<int>(mScreenSize.y / mTileMap.size());

	int rowIdx = 0;
	for (auto& tileMapRow : mTileMap)
	{
		int colIdx = 0;
		for (auto& tile : tileMapRow)
		{
			if (tile != -1)
			{
				dstRect.x = static_cast<int>(colIdx * dstRect.w);
				dstRect.y = static_cast<int>(rowIdx * dstRect.h);

				SDL_Texture* tileTex = mTileTextures[tile];
				SDL_RenderCopy(renderer, tileTex, nullptr, &dstRect);
			}
			++colIdx;
		}
		++rowIdx;
	}
}