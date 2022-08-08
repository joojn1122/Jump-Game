#include "Player.hpp"
#include "Platform.hpp"
#include "JumpGame.hpp"
#include "RenderWindow.hpp"
#include <SDL.h>

Player::Player()
{
	SDL_Texture* right_texture = RenderWindow::getInstance().loadTexture("character_right.png");
	SDL_Texture* left_texture = RenderWindow::getInstance().loadTexture("character_left.png");
	
	textures.push_back(left_texture);
	textures.push_back(right_texture);
}

void Player::jump()
{
	jumping = true;
	jump_velocity = jump_height;
}

void Player::updateAndDraw(JumpGame* game)
{
	if (this->jumping)
	{
		this->prevY = this->y;
		this->y += this->jump_velocity;

		this->jump_velocity -= this->jump_gravity;
	}

	if (this->getDrawingY() - (game->getScore() - this->y) + this->height < 0)
	{
		game->game_over();
		return;
	}

	RenderWindow::getInstance().draw(
		this->x,
		this->getDrawingY() - (game->getScore() - this->y),
		this->width,
		this->height,
		this->textures[this->direction]
	);
}

int Player::getDrawingY()
{
	int h;
	RenderWindow::getInstance().getWindowSize(NULL, &h);

	return h / 2;
}


void Player::move_side(int val)
{
	this->prevX = this->x;
	this->x += val;
}

bool Player::isInPoint(int x2, int y2, int width2, int height2)
{
	/*
	std::cout << "this->x: " << this->x << std::endl;
	std::cout << "this->y: " << this->y << std::endl;
	std::cout << "this->w: " << this->width << std::endl;
	std::cout << "this->h: " << this->height << std::endl;

	std::cout << "x2: " << x2 << std::endl;
	std::cout << "y2: " << y2 << std::endl;
	std::cout << "w2: " << width2 << std::endl;
	std::cout << "h2: " << height2 << std::endl;
	*/

	// X
	bool x_ = (this->x + this->width) > x2 && this->x < (x2 + width2);

	if (!x_)
	{
		for (
			int i = (this->prevX > this->x ? this->x : this->prevX);
			i < (this->prevX > this->x ? this->prevX : this->x);
			i++
			)
		{
			if (i + this->width > x2 && i < x2 + width2)
			{
				x_ = true;
			}
		}
	}
	
	// Y
	bool y_ = this->y > y2 && this->y < (y2 + height2);

	if (!y_)
	{
		for (
			int i = (this->prevY > this->y ? this->y : this->prevY);
			i < (this->prevY > this->y ? this->prevY : this->y);
			i++
			)
		{
			if (i > y2 && i < y2 + height2)
			{
				y_ = true;
			}
		}
	}
	
	return x_ && y_;
}