#include "TileMapComponent.h"
#include <fstream>
#include <sstream>
#include <iostream>

TileMapComponent::TileMapComponent(Actor* owner, int updateOrder)
	: SpriteComponent(owner, updateOrder)
{
}

void TileMapComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
}

void TileMapComponent::LoadCSV(const std::string& fileName)
{
	std::ifstream tileMap(fileName);

	if (!tileMap)
	{
		SDL_Log("Failed to open tile map file: %s", fileName.c_str());
		return;
	}

	std::string tilesRowStr;
	while (std::getline(tileMap, tilesRowStr))
	{
		std::vector<int> addTilesRow;
		std::string tileStr;
		std::istringstream iss(tilesRowStr);

		while (std::getline(iss, tileStr, ','))
		{
			int tile = std::stoi(tileStr);
			addTilesRow.emplace_back(tile);
		}

		mTileMap.push_back(addTilesRow);
	}
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