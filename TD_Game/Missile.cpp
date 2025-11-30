#include "Missile.h"
#include "SpriteComponent.h"
#include "ResourceManger.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "Enemy.h"
#include "AIComponent.h"

Missile::Missile(Game* game, Enemy* enemy, const Vector2& pos)
	:Actor(game)
	,mTargetEnemy(enemy)
{
	SetPos(pos);
	std::unique_ptr<SpriteComponent> sc = std::make_unique<SpriteComponent>(this);
	sc->SetTexture(mGame->GetResourceManager()->GetTexture("Assets/Missile.png", mGame->GetRenderer()));

	std::unique_ptr<MoveComponent> mc = std::make_unique<MoveComponent>(this);
	mc->SetForwardSpeed(100.0f);

	std::unique_ptr<CircleComponent> cc = std::make_unique<CircleComponent>(this);
	mCircle = cc.get();
	cc->SetRadius(16.0f);

	AddComponent(std::move(sc));
	AddComponent(std::move(mc));
	AddComponent(std::move(cc));
}

void Missile::UpdateActor(float deltaTime)
{
	const auto& enemies = Game::Get().GetEnemies();
	auto iter = std::find(enemies.begin(), enemies.end(), mTargetEnemy);
	if (iter == enemies.end())
	{
		SetState(State::EDead);
		return;
	}
	if (Intersect(*mCircle, *mTargetEnemy->GetCircle()))
	{
		mTargetEnemy->GetAI()->ChangeState("Death");
		SetState(State::EDead);
	}
}
