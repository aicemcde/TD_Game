#pragma once
#include "Component.h"
#include <SDL.h>

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int updateOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);
	void SetRendererFlip(bool vertical, bool horizontal);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

private:
	SDL_RendererFlip mRendererFlip = SDL_FLIP_NONE;
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};