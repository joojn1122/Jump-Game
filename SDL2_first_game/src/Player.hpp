#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>

class JumpGame;

class Player {

public:

	Player();

	void jump();
	void updateAndDraw(JumpGame* game);

	std::vector<SDL_Texture*> getTextures() {
		return this->textures;
	};

	int getX() { 
		return this->x;
	}

	int getY() {
		return this->y;
	}

	int width = 50;
	int height = 100;
	int x = 0;

	double getJumpVelocity()
	{
		return jump_velocity;
	}

	int move_speed = 10;

	bool isJumping()
	{
		return jumping;
	}

	void move_side(int val);
	bool isInPoint(int x, int y, int width, int height);
	int getDrawingY();

	/*
	    Direction of the player
		0 == Left
		1 == Right
	*/
	int direction = 0;

private:

	int y = 0;
	

	bool jumping = false;
	int jump_height = 20;
	double jump_velocity, jump_gravity = 0.6;

	int prevX, prevY;

	std::vector<SDL_Texture*> textures;
};