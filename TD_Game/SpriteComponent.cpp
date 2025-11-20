#include "SpriteComponent.h"
#include "Actor.h"

SpriteComponent::SpriteComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mDrawOrder(updateOrder)
	, mTexture(nullptr)
	, mTexHeight(0)
	, mTexWidth(0)
{
	mOwner->GetGame()->GetScene()->AddSpriteComponent(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetScene()->RemoveSpriteComponent(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		r.x = static_cast<int>(mOwner->GetPos().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPos().y - r.h / 2);
		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, Math::ToDegrees(mOwner->GetRot()), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	if (mTexture)
	{
		SDL_QueryTexture(mTexture, nullptr, nullptr, &mTexWidth, &mTexHeight);
	}
}