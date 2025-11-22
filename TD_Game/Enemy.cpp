#include "Enemy.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "ResourceManger.h"
#include "NavComponent.h"


Enemy::Enemy(Game* game)
	:Actor(game)
{
	std::unique_ptr<SpriteComponent> sc = std::make_unique<SpriteComponent>(this);
	sc->SetTexture(game->GetResourceManager()->GetTexture("Assets/Airplane.png", game->GetRenderer()));
	mSprComp = sc.get();

	std::unique_ptr<NavComponent> nc = std::make_unique<NavComponent>(this);
	nc->SetForwardSpeed(64.0f);
	mNavComp = nc.get();

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