#include "Turret.h"
#include "SpriteComponent.h"
#include "ResourceManger.h"
#include "AIComponent.h"
#include "AIShot.h"
#include "AIDeath.h"
#include "Missile.h"
#include "Scene.h"
#include <cfloat>
#include <vector>
#include "Enemy.h"

Turret::Turret(Game* game, const Vector2& centerPos)
	:Actor(game)
	,mAttackRange(256.0f)
{
	SetPos(centerPos);

	std::unique_ptr<SpriteComponent> sc = std::make_unique<SpriteComponent>(this, 20);
	sc->SetTexture(mGame->GetResourceManager()->GetTexture("Assets/Tower.png", mGame->GetRenderer()));
	mSprComp = sc.get();

	std::unique_ptr<AIComponent> aic = std::make_unique<AIComponent>(this);
	mAIComp = aic.get();
	aic->RegisterState(std::make_unique<AIShot>(mAIComp));
	aic->RegisterState(std::make_unique<AIDeath>(mAIComp));
	aic->ChangeState("Shot");

	AddComponent(std::move(sc));
	AddComponent(std::move(aic));
}

void Turret::UpdateActor(float deltaTime)
{
	SearchEnemy();
	AttackTarget(deltaTime);
}

void Turret::SearchEnemy()
{
	if (mCurrentEnemy != nullptr)
	{
		mCurrentEnemy = nullptr;
	}

	const std::vector<Enemy*>& enemies = Game::Get().GetEnemies();
	Enemy* nearestEnemy = nullptr;
	float minDistanceSq = FLT_MAX;
	float attackRangeSq = mAttackRange * mAttackRange;
	for (Enemy* enemy : enemies)
	{
		if (enemy == nullptr) continue;
		Vector2 diff = GetPos() - enemy->GetPos();
		float distSq = diff.LengthSq();
		if (distSq <= attackRangeSq && distSq < minDistanceSq)
		{
			minDistanceSq = distSq;
			nearestEnemy = enemy;
		}
	}
	mCurrentEnemy = nearestEnemy;
}

void Turret::AttackTarget(float deltaTime)
{
	if (mCurrentEnemy == nullptr) return;
	mMissileCooldown -= deltaTime;
	Vector2 dir = mCurrentEnemy->GetPos() - GetPos();
	float angle = Math::Atan2(-dir.y, dir.x);
	SetRot(angle);
	if (mMissileCooldown <= 0.0f)
	{
		float missileAngle = angle;
		std::unique_ptr<Missile> mMissile = std::make_unique<Missile>(mGame, mCurrentEnemy, mCenterPosition);
		mMissile->SetRot(missileAngle);
		mGame->GetScene()->AddActor(std::move(mMissile));
		mMissileCooldown = 1.0f;
	}
}

