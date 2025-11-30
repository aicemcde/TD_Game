#include "MouseInputComponent.h"
#include "Game.h"
#include "Actor.h"
#include "Turret.h"
#include "Scene.h"

MouseInputComponent::MouseInputComponent(Actor* owner, const TileMapData& map)
	:Component(owner)
	,mTileMap(map)
{
	if (mTileMap.empty())
	{
		SDL_Log("MIC : TileMap is empty");
		Game::Get().Shutdown();
		return;
	}
}

bool MouseInputComponent::IsValidIndex(int x, int y)
{
	if (y < 0 || y >= mTileMap.size()) return false;
	if (x < 0 || x >= mTileMap[0].size()) return false;

	return true;
}

void MouseInputComponent::ProcessInput(const uint8_t* keyState)
{
	int x, y;
	int mouseBottonState = SDL_GetMouseState(&x, &y);
	mMousePos.x = static_cast<float>(x);
	mMousePos.y = static_cast<float>(y);

	mIsDownMouse = (mouseBottonState & SDL_BUTTON(SDL_BUTTON_LEFT));
}

void MouseInputComponent::Update(float deltaTime)
{
	Vector2 tileSize = Game::Get().GetTileSize();
	int indexX = static_cast<int>(mMousePos.x / tileSize.x);
	int indexY = static_cast<int>(mMousePos.y / tileSize.y);

	

	if (IsValidIndex(indexX, indexY))
	{
		if (mLastIndexX != indexX || mLastIndexY != indexY)
		{
			if (mLastIndexX != -1)
			{
				Data& prevTile = mTileMap[mLastIndexY][mLastIndexX];
				if (prevTile.mHadTurret)
				{
				}
				else if (prevTile.mTileType == TileTypes::SELECTEDNORMALGROUND)
				{
					prevTile.mTileType = TileTypes::NORMALGROUND;
				}
			}
			Data& currentTile = mTileMap[indexY][indexX];
			if (currentTile.mTileType == NORMALGROUND)
			{
				currentTile.mTileType = TileTypes::SELECTEDNORMALGROUND;
			}
			mLastIndexX = indexX;
			mLastIndexY = indexY;
		}

		if (mIsDownMouse)
		{
			Data& currentTile = mTileMap[indexY][indexX];
			if (currentTile.mTileType == TileTypes::SELECTEDNORMALGROUND || currentTile.mTileType == TileTypes::NORMALGROUND)
			{
				currentTile.mTileType = TileTypes::TURRETBASEGROUND;
				currentTile.mHadTurret = true;
				std::unique_ptr<Turret> turret = std::make_unique<Turret>(&Game::Get(), currentTile.mCenterPos);
				Game::Get().GetScene()->AddActor(std::move(turret));
			}
		}
	}
	else
	{
		if (mLastIndexX != -1) mLastIndexX = -1; mLastIndexY = -1;
	}
}