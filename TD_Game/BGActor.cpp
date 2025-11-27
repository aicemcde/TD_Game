#include "BGActor.h"
#include "TileMapComponent.h"
#include "MapLoaderComponent.h"
#include "MouseInputComponent.h"
#include "ResourceManger.h"

BGActor::BGActor(Game* game)
	:Actor(game)
{
	Vector2 screenSize = Game::Get().GetScreenSize();
	SetPos(screenSize * Vector2(0.5f, 0.5f));
	
	std::unique_ptr<TileMapComponent> tmc = std::make_unique<TileMapComponent>(this);			//mapの描画
	std::unique_ptr<MapLoaderComponent> mlc = std::make_unique<MapLoaderComponent>(this, "Assets/MapLayer.csv");		//CSVの読み込み、GridDataの作成
	mTMComp = tmc.get();

	//テクスチャの読み込みとセット
	SDL_Texture* tstex = mGame->GetResourceManager()->GetTexture("Assets/TileGreen.png", mGame->GetRenderer());
	tmc->SetTileTexture(TileTypes::NORMALGROUND, tstex);
	tstex = mGame->GetResourceManager()->GetTexture("Assets/TileGreenSelected.png", mGame->GetRenderer());
	tmc->SetTileTexture(TileTypes::SELCTEDNORMALGROUND, tstex);
	tstex = mGame->GetResourceManager()->GetTexture("Assets/TileGrey.png", mGame->GetRenderer());
	tmc->SetTileTexture(TileTypes::TURRETBASEGROUND, tstex);
	tstex = mGame->GetResourceManager()->GetTexture("Assets/TileBrown.png", mGame->GetRenderer());
	tmc->SetTileTexture(TileTypes::LOAD, tstex);
	tmc->SetTileTexture(TileTypes::START, tstex);
	tmc->SetTileTexture(TileTypes::GOAL, tstex);

	tmc->SetTileMap(mlc->GetMap());
	Game::Get().SetLevel(mlc->BuildGraphFromGrid());

	std::unique_ptr<MouseInputComponent> mic = std::make_unique<MouseInputComponent>(this, mlc->GetMap());
	mTileMap = mic->GetMap();
	mMIComp = mic.get();

	AddComponent(std::move(tmc));
	AddComponent(std::move(mic));
}

void BGActor::UpdateActor(float deltaTime)
{
	mTileMap = mMIComp->GetMap();
	mTMComp->SetTileMap(mTileMap);
}

