#pragma once

#include "GuiScreen.hpp"

class JumpGame;

class GuiGameOver : public GuiScreen {

public:

	GuiGameOver(JumpGame* game) : game(game) {};

	void drawScreen();

private:

	JumpGame* game;
};