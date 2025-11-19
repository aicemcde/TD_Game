#include "ResourceManger.h"

SDL_Texture* ResourceManager::GetTexture(const char* fileName, SDL_Renderer* renderer)
{
	std::string s(fileName);
	auto iter = mTextures.find(s);
	if (iter != mTextures.end())
	{
		return iter->second;
	}

	SDL_Surface* surface = IMG_Load(fileName);
	if (!surface)
	{
		SDL_Log("画像の読み込みに失敗しました: %s", IMG_GetError());
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		SDL_Log("テクスチャの作成に失敗しました: %s", SDL_GetError());
		return nullptr;
	}

	mTextures.emplace(s, texture);
	return texture;
}

void ResourceManager::Unload()
{
	for (auto iter : mTextures)
	{
		SDL_DestroyTexture(iter.second);
	}
	mTextures.clear();
}