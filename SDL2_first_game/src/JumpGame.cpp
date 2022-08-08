#pragma once

#include "JumpGame.hpp"
#include "Platform.hpp"
#include "RenderWindow.hpp"
#include "FontRenderer.hpp"
#include <vector>
#include <iostream>
#include <string>
#include "GuiGameOver.hpp"
#include "Textures.hpp"

JumpGame::JumpGame(Player* player)
	:player(player)
{
	// generate platforms
	int h;
	RenderWindow::getInstance().getWindowSize(NULL, &h);

	for (int i = 0; i < (h * 2); i += 200)
	{
		this->generatePlatform(i);
	}
}

void JumpGame::drawScreen()
{
	//int refreshRate = RENDER_WINDOW.getRefreshRate();

	
	// play game
	int w, h;
	RenderWindow::getInstance().getWindowSize(&w, &h);

	int grass_height = 100;

	RenderWindow::getInstance().draw(0, 0, w, grass_height, Textures::getTexture("grass"));
	RenderWindow::getInstance().draw(0, grass_height, w, h - grass_height, Textures::getTexture("sky"));

	std::string s = "Score: " + std::to_string(getScore() / PLATFORM_SPACE);
	int string_w;

	FontRenderer::getArial().getTextSize(s, &string_w, NULL);
	FontRenderer::getArial().renderText(s, (w * 0.5) - (string_w * 0.5), 10, { 0, 0, 0 });

	// move left
	if (RenderWindow::getInstance().keyPressed(SDLK_LEFT)
		|| RenderWindow::getInstance().keyPressed(SDLK_a))
	{
		if (player->x > 0)
		{
			player->direction = 0;
			player->move_side(-player->move_speed);
		}
	}
	// move right
	if (RenderWindow::getInstance().keyPressed(SDLK_RIGHT) 
		|| RenderWindow::getInstance().keyPressed(SDLK_d))
	{
		if (player->x + player->width + 1 < w)
		{
			player->direction = 1;
			player->move_side(player->move_speed);
		}
	}

	Platform* platform_p = this->getPlatformAndDraw();

	if (player->getY() < 1)
	{
		player->jump(); 
	}
	else if (platform_p != NULL)
	{
		platform_p->handleJump(this);
		player->jump();
	}

	player->updateAndDraw(this);

	int score = player->getY();
	if (score > this->score)
	{
		this->score = score;
	}

	if (getPlatforms().size() < 20)
	{
		this->generatePlatform(NULL);
	}
}

int JumpGame::getHighestPlatform()
{
	/*if (platforms.size() == 0) return nullptr;

	return platforms[platforms.size() - 1];
	*/

	// maybe
	int h = 0;

	for (int i = 0; i < platforms.size(); i++)
	{
		Platform* platform = platforms[i];

		if (platform->getY() > h)
		{
			h = platform->getY();
		}
	}

	return h;
}

void JumpGame::generatePlatform(int y)
{
	int highest_platform = getHighestPlatform();
	if (highest_platform == NULL && y == NULL)
	{
		return;
	}

	int y_ = y == NULL ? highest_platform + 200 : y;

	switch (random_number(0, 2))
	{
		case 0:

			{
				SolidPlatform* p = new SolidPlatform(y_);

				this->platforms.push_back(p);
			}
			
			break;

		case 1:

			{
				CloudPlatform* p1 = new CloudPlatform(y_);

				this->platforms.push_back(p1);
			}
			
			break;
	}
}

void JumpGame::addPlatform(Platform* platform)
{
	this->platforms.push_back(platform);
}

Platform* JumpGame::getPlatformAndDraw()
{
	// not falling
	Platform* platform_p = NULL;

	for (Platform* platform : platforms)
	{
		// update platform
		platform->updateAndDraw(this);
		
		if (
			((player->isJumping() && player->getJumpVelocity() < 0) 
				|| !player->isJumping()) // falling down
			&& player->isInPoint(
				platform->getX(),
				platform->getY(),
				platform->getWidth(),
				platform->getHeight()
				)
			)
		{
			platform_p = platform;
		}
	}

	return platform_p;
}

Player* JumpGame::getPlayer()
{
	return this->player;
}

void JumpGame::removePlatform(Platform* platform)
{
	for (int i = 0; i < platforms.size(); i++)
	{
		if (platforms[i] == platform)
		{
			platforms.erase(platforms.begin() + i);
			break;
		}
	}
}

void JumpGame::game_over()
{
	game_ended = true;
	RenderWindow::getInstance().currentScreen = new GuiGameOver(this);
}


int random_number(int min, int max)
{
	return min + (rand() % (max - min));
}
