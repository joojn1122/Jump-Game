#pragma once

#include <SDL_TTF.h>
#include <SDL.h>
#include <iostream>

struct FontRenderer {

	FontRenderer(std::string font_name, int size);
	
	int renderText(std::string text, int x, int y, SDL_Color color);

	/*
	   Params: Text, width_pointer -> so the width will be passed into that var, height_pointer etc.
	   You can also pass NULL as pointer
	*/
	void getTextSize(std::string text, int* width_pointer, int* height_pointer);
	
	int FONT_HEIGHT;

	TTF_Font* font;

	static FontRenderer& getArial()
	{
		static FontRenderer arial("Arial.ttf", 30);

		return arial;
	}
};