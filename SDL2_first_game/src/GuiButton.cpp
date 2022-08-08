#include "GuiButton.hpp"
#include "RenderWindow.hpp"
#include "Textures.hpp"
#include <SDL.h>

void GuiButton::draw(int mouseX, int mouseY)
{
	int w, h;
	RenderWindow::getInstance().getWindowSize(&w, &h);

	/*
	SDL_Color color;

	if (mouseOver(mouseX, mouseY))
	{
		color = { 255, 100, 100 };
	}
	else {
		color = { 255, 0, 0 };
	}*/

	int size_up = mouseOver(mouseX, mouseY) ? 10 : 0;

	RenderWindow::getInstance().draw(
		(w * x) - (width / 2) - (size_up / 2),
		(h * y) - (height / 2) - (size_up / 2),

		width + size_up,
		height + size_up,

		Textures::getTexture("button")
	);

	int text_w;
	fontRenderer->getTextSize(text, &text_w, NULL);
	fontRenderer->renderText(
		text,
		(w * x) - (text_w / 2),
		(h * y) - (fontRenderer->FONT_HEIGHT / 2),
		{ 255, 255, 255 }
	);
}

bool GuiButton::mouseOver(int mouseX, int mouseY) {
	int w, h;
	RenderWindow::getInstance().getWindowSize(&w, &h);

	return mouseX > (w * x) - (width / 2)
		&& mouseX < (w* x) + (width / 2)
		&& mouseY > (h * y) - (height / 2)
		&& mouseY < (h* y) + (height / 2);
}