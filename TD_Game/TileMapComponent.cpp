#include "TileMapComponent.h"
#include "Game.h"

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
	const Vector2 tileSize = Game::Get().GetTileSize();
	dstRect.w = static_cast<int>(tileSize.x);
	dstRect.h = static_cast<int>(tileSize.y);

	int rowIdx = 0;
	for (auto& tileMapRow : mTileMap)
	{
		int colIdx = 0;
		for (auto& tile : tileMapRow)
		{
			if (tile.mTileType != -1)
			{
				dstRect.x = static_cast<int>(colIdx * dstRect.w);
				dstRect.y = static_cast<int>(rowIdx * dstRect.h);

				SDL_Texture* tileTex = mTileTextures[tile.mTileType];
				SDL_RenderCopy(renderer, tileTex, nullptr, &dstRect);
			}
			++colIdx;
		}
		++rowIdx;
	}
}