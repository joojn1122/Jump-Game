#pragma once

#include <iostream>
#include "FontRenderer.hpp"
#include <vector>

class GuiButton {

public:
	/*
		x - between 0 and 1 => size of screen = 0.5 == half screen
		y - same
	*/
	GuiButton(int id, FontRenderer* fontRenderer, std::string text, float x, float y, int width, int height)
		:id(id), text(text), x(x), y(y), width(width), height(height), fontRenderer(fontRenderer) {

	}
	
	void draw(int mouseX, int mouseY);
	bool mouseOver(int mouseX, int mouseY);

	int id;

private:

	float x, y;
	int width, height;
	std::string text;
	FontRenderer* fontRenderer;
};