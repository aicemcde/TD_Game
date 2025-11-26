#include "MouseInputComponent.h"
#include "Game.h"
#include "Actor.h"

MouseInputComponent::MouseInputComponent(Actor* owner)
	:Component(owner)
{

}

void MouseInputComponent::ProcessInput(const uint8_t* keyState)
{
	int mousePos_x = 0;
	int mousePos_y = 0;
	int mouseBottonState = SDL_GetMouseState(&mousePos_x, &mousePos_y);
	int posCount = 0;
	for (auto pos : mCanBuildTurretPoss)
	{
		int tilePos_x = static_cast<int>(mPossForMap[posCount].x);
		int tilePos_y = static_cast<int>(mPossForMap[posCount].y);
		
		if (mTileMap[tilePos_x][tilePos_y] == 11)
		{
			mTileMap[tilePos_x][tilePos_y] = 1;
		}
		if (mTileMap[tilePos_x][tilePos_y] == 1 && mousePos_x > pos.x && mousePos_x < pos.x + mTileSize.x && mousePos_y > pos.y && mousePos_y < pos.y + mTileSize.y)
		{
			
			mTileMap[tilePos_x][tilePos_y] = 11;
			if (mouseBottonState == 1)
			{
				mTileMap[tilePos_x][tilePos_y] = 22;
			}
		}
		++posCount;
	}
}

void MouseInputComponent::Initialize(const GridData& map)
{
	mTileMap = map;
	if (mTileMap.empty())
	{
		SDL_Log("MouseInputComp : TileMap is empty");
		return;
	}
	const int Rows = static_cast<int>(mTileMap.size());
	const int Cols = static_cast<int>(mTileMap[0].size());

	mTileSize.x = mScreenSize.x / Cols;
	mTileSize.y = mScreenSize.y / Rows;

	SDL_Log("mic : row,%d col,%d", Rows, Cols);

	for (int rowCount = 0; rowCount < Rows; ++rowCount)
	{
		for (int colCount = 0; colCount < Cols; ++colCount)
		{
			if (mTileMap[rowCount][colCount] == 1)
			{
				float x = colCount * mTileSize.x;
				float y = rowCount * mTileSize.y;
				mCanBuildTurretPoss.emplace_back(Vector2(x, y));
				mPossForMap.emplace_back(Vector2(static_cast<float>(rowCount), static_cast<float>(colCount)));
			}
		}
	}
}