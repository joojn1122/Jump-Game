#pragma once

#include <iostream>
#include <vector>

class GuiButton;

struct GuiScreen {

	virtual void drawScreen() = 0;

	std::vector<GuiButton*> buttons;
};