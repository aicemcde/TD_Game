#include "Missile.h"
#include "SpriteComponent.h"
#include "ResourceManger.h"
#include "CircleComponent.h"
#include "MoveComponent.h"

Missile::Missile(Game* game)
	:Actor(game)
{
	std::unique_ptr<SpriteComponent> sc = std::make_unique<SpriteComponent>(this);
	sc->SetTexture(mGame->GetResourceManager()->GetTexture("Assets/Missile.png", mGame->GetRenderer()));

	std::unique_ptr<MoveComponent> mc = std::make_unique<MoveComponent>(this);
	mc->SetForwardSpeed(800.0f);

	std::unique_ptr<CircleComponent> cc = std::make_unique<CircleComponent>(this);
	mCircle = cc.get();
	cc->SetRadius(32.0f);

	AddComponent(std::move(sc));
	AddComponent(std::move(mc));
	AddComponent(std::move(cc));
}
