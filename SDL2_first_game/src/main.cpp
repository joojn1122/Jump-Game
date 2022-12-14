#include "RenderWindow.hpp"
#include "FontRenderer.hpp"
#include "Player.hpp"
#include "JumpGame.hpp"
#include "Utils.hpp"
#include <string>
#include <cstdlib>
#include <ctime>
#include "GuiTitle.hpp"

/*
	Libs folder: Linker -> General -> Additional Lib Folders
	Libs: Linker -> Input -> Libs -> add example (SDL2.lib)

	Include: C++ -> General -> Additional Include Folders
*/

int main(int argc, char* argv[])
{
	// init render window
	RenderWindow::getInstance();

	// set current screen
	RenderWindow::getInstance().currentScreen = new GuiTitle();

	const float timeStep = 0.01f; // 1 / 100 (100fps)
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();
	float currentTimer = SDL_GetTicks64();

	while (RenderWindow::getInstance().isRunning)
	{
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;
		while (accumulator >= timeStep)
		{
			RenderWindow::getInstance().handleEvents();
			
			/*
			// 20 times per second

			long time = SDL_GetTicks64();
			if (time - currentTimer > 1000 / 20)
			{
				currentTimer = time;
				// there
				jump_game.onTick();
			}
			*/

			accumulator -= timeStep;
		}


		if (RenderWindow::getInstance().currentScreen != nullptr)
		{
			// display
			RenderWindow::getInstance().clear();

			RenderWindow::getInstance().currentScreen->drawScreen();

			RenderWindow::getInstance().display(); 
		}
	}

	RenderWindow::getInstance().destroy();

	return 0;
}
