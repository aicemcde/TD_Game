#include "BGActor.h"
#include "TileMapComponent.h"
#include "MapLoaderComponent.h"
#include "MouseInputComponent.h"
#include "ResourceManger.h"
#include "Turret.h"
#include "Scene.h"

BGActor::BGActor(Game* game)
	:Actor(game)
{
	SetPos(mScreenSize * Vector2(0.5f, 0.5f));
	
	std::unique_ptr<TileMapComponent> tmc = std::make_unique<TileMapComponent>(this);			//mapの描画
	std::unique_ptr<MapLoaderComponent> mlc = std::make_unique<MapLoaderComponent>(this);		//CSVの読み込み、GridDataの作成
	std::unique_ptr<MouseInputComponent> mic = std::make_unique<MouseInputComponent>(this);
	mTMComp = tmc.get();
	mMIComp = mic.get();

	//テクスチャの読み込みとセット
	tmc->SetScreenSize(mScreenSize);
	SDL_Texture* tstex = mGame->GetResourceManager()->GetTexture("Assets/TileGreen.png", mGame->GetRenderer());
	tmc->SetTileTexture(1, tstex);
	tstex = mGame->GetResourceManager()->GetTexture("Assets/TileGreenSelected.png", mGame->GetRenderer());
	tmc->SetTileTexture(11, tstex);
	tstex = mGame->GetResourceManager()->GetTexture("Assets/TileGrey.png", mGame->GetRenderer());
	tmc->SetTileTexture(22, tstex);
	tstex = mGame->GetResourceManager()->GetTexture("Assets/TileBrown.png", mGame->GetRenderer());
	tmc->SetTileTexture(2, tstex);
	tmc->SetTileTexture(100, tstex);	//START
	tmc->SetTileTexture(200, tstex);	//GOAL

	mlc->LoadCSV("Assets/MapLayer.csv");
	tmc->SetTileMap(mlc->GetMap());
	mLevel = mlc->BuildGraphFromGrid(mScreenSize);

	mic->SetScreenSize(mScreenSize);
	mic->Initialize(mlc->GetMap());
	mTileMap = mic->GetMap();

	AddComponent(std::move(tmc));
	AddComponent(std::move(mic));
}

void BGActor::UpdateActor(float deltaTime)
{
	mTileMap = mMIComp->GetMap();
	mTMComp->SetTileMap(mTileMap);
	
}

void BGActor::GenerateTurret()
{
	for (auto& tileMapRow : mTileMap)
	{
		for (auto& tileMapCol : tileMapRow)
		{
			if (tileMapCol == 22)
			{
				std::unique_ptr<Turret> turret = std::make_unique<Turret>(mGame);
				int w = static_cast<int>(mScreenSize.x / mTileMap[0].size());
				int h = static_cast<int>(mScreenSize.y / mTileMap.size());
				turret->SetPos(Vector2(mTileMap.size() * w, mTileMap[0].size() * h));
				mGame->GetScene()->AddActor(std::move(turret));
			}
		}
	}
}