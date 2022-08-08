#include "GuiTitle.hpp"
#include "RenderWindow.hpp"
#include "FontRenderer.hpp"
#include "GuiButton.hpp"
#include "JumpGame.hpp"
#include "Textures.hpp"

GuiTitle::GuiTitle() : GuiScreen() {

	buttons.push_back(
		new GuiButton(1, &FontRenderer::getArial(), "Play", 0.5f, 0.5f, 300, 100)
	);

}

void GuiTitle::drawScreen()
{
	Textures::drawBackground();

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	for (GuiButton* button : buttons)
	{
		// draw button
		button->draw(mouseX, mouseY);

		if (button->mouseOver(mouseX, mouseY) && RenderWindow::getInstance().mouseClicked(SDL_BUTTON_LEFT))
		{
			if (button->id == 1)
			{
				RenderWindow::getInstance().currentScreen = new JumpGame(new Player());
			}
		}
	}
}