#pragma once

#include <iostream>
#include <vector>
#include "Platform.hpp"
#include "Player.hpp"
#include "GuiScreen.hpp"
#include <map>

class FontRenderer;

int random_number(int min, int max);

class JumpGame : public GuiScreen {

public:
	JumpGame(Player* player);

	void drawScreen();
	void addPlatform(Platform* platform);
	void removePlatform(Platform* platform);
	void game_over();

	Player* getPlayer();

	int getScore()
	{
		return this->score;
	}

	std::vector<Platform*> getPlatforms()
	{
		return this->platforms;
	}

	void generatePlatform(int y);

private:

	int score = 0;
	Player* player;
	bool game_ended = false;
	
	Platform* getPlatformAndDraw();
	int getHighestPlatform();

	std::vector<Platform*> platforms;
};