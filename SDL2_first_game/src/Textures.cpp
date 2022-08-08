#include "Textures.hpp"
#include "RenderWindow.hpp"

SDL_Texture* Textures::getTexture(std::string name)
{
	return getInstance().textures[name];
}

Textures::Textures()
{
	textures.insert({
		"grass", RenderWindow::getInstance().loadTexture("grass.jpg")
	});

	textures.insert({
		"sky", RenderWindow::getInstance().loadTexture("sky.jpg")
	});

	textures.insert({
		"button", RenderWindow::getInstance().loadTexture("button.png")
	});
}

void Textures::drawBackground()
{
	int w, h;
	RenderWindow::getInstance().getWindowSize(&w, &h);

	int grass_height = 100;

	RenderWindow::getInstance().draw(0, 0, w, grass_height, getTexture("grass"));
	RenderWindow::getInstance().draw(0, grass_height, w, h - grass_height, getTexture("sky"));
}