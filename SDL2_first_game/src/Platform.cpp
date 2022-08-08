#include "Platform.hpp"
#include "JumpGame.hpp"
#include "RenderWindow.hpp"

Platform::Platform(SDL_Texture* texture, int y)
	:y(y), texture(texture)
{

	int w;
	RenderWindow::getInstance().getWindowSize(&w, nullptr);

	x = random_number(0, w - this->getWidth());

}

void Platform::super_update(JumpGame* game)
{
	if ((this->getY() - (game->getScore()) + game->getPlayer()->getDrawingY() + this->getWidth()) < 0)
	{
		game->removePlatform(this);
		return;
	}

	RenderWindow::getInstance().draw(
		this->getX(),
		this->getY() - (game->getScore()) + game->getPlayer()->getDrawingY(),
		this->getWidth(),
		this->getHeight(),
		this->getTexture()
	);
}

SolidPlatform::SolidPlatform(int y) : Platform(nullptr, y)
{
	texture = RenderWindow::getInstance().loadTexture("solid_platform.png");
}

CloudPlatform::CloudPlatform(int y) : Platform(nullptr, y)
{
	texture = RenderWindow::getInstance().loadTexture("cloud_platform.png");
}

void SolidPlatform::handleJump(JumpGame* game) {
	//std::cout << "Jumped on solid\n";
}

void SolidPlatform::updateAndDraw(JumpGame* game) {
	super_update(game);

	//std::cout << "Removed cloud\n";
}

void CloudPlatform::handleJump(JumpGame* game) {
	jumped = true;
}

void CloudPlatform::updateAndDraw(JumpGame* game) {
	

	if (jumped)
	{
		currentFrame++;

		// draw a: fadeTime - currentFrame;

		if (currentFrame > fadeTime or true) // TODO: add fading
		{
			game->removePlatform(this);
			return;
		}
		/*
		SDL_Renderer* renderer = RenderWindow::getInstance().getRenderer();
		
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, fadeTime - currentFrame);
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, texture);
		*/

		RenderWindow::getInstance().draw(
			this->getX(),
			this->getY() - (game->getScore()) + game->getPlayer()->getDrawingY(),
			this->getWidth(),
			this->getHeight(),
			this->getTexture()
		);

	}
	else
	{
		super_update(game);
	}
}