#include "Enemy.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "ResourceManger.h"
#include "NavComponent.h"
#include "AIComponent.h"
#include "AIMove.h"
#include "AIDeath.h"

Enemy::Enemy(Game* game)
	:Actor(game)
{
	std::unique_ptr<SpriteComponent> sc = std::make_unique<SpriteComponent>(this);
	sc->SetTexture(mGame->GetResourceManager()->GetTexture("Assets/Airplane.png", mGame->GetRenderer()));
	mSprComp = sc.get();

	std::unique_ptr<NavComponent> nc = std::make_unique<NavComponent>(this);
	nc->SetForwardSpeed(64.0f);
	mNavComp = nc.get();

	std::unique_ptr<AIComponent> aic = std::make_unique<AIComponent>(this);
	aic->RegisterState(std::make_unique<AIMove>(aic.get()));
	aic->RegisterState(std::make_unique<AIDeath>(aic.get()));
	mAIComp = aic.get();

	aic->ChangeState("Move");

	AddComponent(std::move(aic));
	AddComponent(std::move(sc));
	AddComponent(std::move(nc));
}

void Enemy::Initialize(const GameLevel& level)
{
	mNavComp->SetPath(level);
	if (mNavComp->HasPath())
	{
		Vector2 firstPos = mNavComp->GetFirstPos();
		firstPos.x -= 32.0f;
		SetPos(firstPos);
		mNavComp->TurnTo(mNavComp->GetNextPos());
		SDL_Log("Enemy Initialize pos(%.1f, %.1f)", firstPos.x, firstPos.y);
	}
	else
	{
		SDL_Log("Enemy Initialize failed: no path");
	}
}

void Enemy::UpdateActor(float deltaTime)
{

	if (mNavComp->GetEnd_of_rute())
	{
		mAIComp->ChangeState("Death");
	}
}