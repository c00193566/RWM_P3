#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <string>

/// <summary>
/// This class is used for loading in textures
/// and using them for different objects.
/// Prevents objects from loading multiple images
/// in.
/// </summary>
/// <author>Jack Keogh</author>

using namespace std;

class TextureHandler
{
public:
	void addTexture(string Tag, string Path, SDL_Renderer * Renderer);

	SDL_Texture * getTexture(string Tag);

	static TextureHandler * Instance()
	{
		if (!THInstance)
		{
			THInstance = new TextureHandler;
		}

		return THInstance;
	}

private:
	static TextureHandler * THInstance;
	map<string, SDL_Texture*> Textures;

	TextureHandler()
	{
		Textures = map<string, SDL_Texture *>();
	}
};