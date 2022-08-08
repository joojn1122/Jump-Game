#pragma once

#include <SDL.h>
#include <iostream>
#include <map>

class Textures {

public:

	static Textures& getInstance()
	{
		static Textures textures;

		return textures;
	}

	static SDL_Texture* getTexture(std::string name);
	static void drawBackground();

private:
	std::map<std::string, SDL_Texture*> textures;

	Textures();
};