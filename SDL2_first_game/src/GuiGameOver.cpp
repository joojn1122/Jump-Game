#include "GuiGameOver.hpp"
#include "GuiButton.hpp"
#include "RenderWindow.hpp"
#include "GuiTitle.hpp"
#include"JumpGame.hpp"
#include <string>
#include "Textures.hpp"

void GuiGameOver::drawScreen()
{
	Textures::drawBackground();

	int w, h;
	RenderWindow::getInstance().getWindowSize(&w, &h);

	if (
		RenderWindow::getInstance().keyPressed(SDLK_SPACE)
		|| RenderWindow::getInstance().mouseClicked(SDL_BUTTON_LEFT)
		|| RenderWindow::getInstance().mouseClicked(SDL_BUTTON_RIGHT)
		)
	{
		RenderWindow::getInstance().currentScreen = new GuiTitle();
	}

	int text_w, text_h;
	std::string s = "Your score: " + std::to_string(game->getScore() / PLATFORM_SPACE);
	FontRenderer::getArial().getTextSize(s, &text_w, &text_h);
	FontRenderer::getArial().renderText(s, (w / 2) - (text_w / 2), (h / 2) - (text_h / 2), { 255, 255, 255 });

}