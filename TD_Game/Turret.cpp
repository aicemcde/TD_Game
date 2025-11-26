#include "Turret.h"
#include "SpriteComponent.h"
#include "ResourceManger.h"
#include "AIComponent.h"
#include "AIShot.h"
#include "AIDeath.h"
#include "Missile.h"
#include "Scene.h"

Turret::Turret(Game* game)
	:Actor(game)
{
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
	mMissileCooldown -= deltaTime;
	if (mMissileCooldown <= 0.0f)
	{
		std::unique_ptr<Missile> mMissile = std::make_unique<Missile>(mGame);
		mGame->GetScene()->AddActor(std::move(mMissile));
		mMissileCooldown = 1.0f;
	}
}

