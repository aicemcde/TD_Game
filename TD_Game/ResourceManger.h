#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <SDL_image.h>

class ResourceManager
{
public:
	SDL_Texture* GetTexture(const char* fileName, SDL_Renderer* renderer);
	void Unload();

private:
	std::unordered_map<std::string, SDL_Texture*> mTextures;
};