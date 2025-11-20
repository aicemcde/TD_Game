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
	if (mNavComp->HasHash())
	{
		Vector2 firstPos = mNavComp->GetFirstPos();
		firstPos.x -= 64.0f;
		firstPos.x -= 32.0f;
		SetPos(firstPos);
	}
	else
	{
		SDL_Log("Enemy Initialize failed: no path");
	}
}