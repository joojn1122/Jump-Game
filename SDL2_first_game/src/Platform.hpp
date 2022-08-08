#pragma once

#include <iostream>
#include <SDL.h>

#define PLATFORM_WIDTH 100
#define PLATFORM_HEIGHT 30
#define PLATFORM_SPACE 150

class JumpGame;

class Platform {

public:	

	Platform(SDL_Texture* texture, int y);

	virtual void handleJump(JumpGame* game) = 0;
	virtual void updateAndDraw(JumpGame* game) = 0;

	void super_update(JumpGame* game);

	int getX() {
		return x;
	};
	
	int getY()
	{
		return y;
	}

	int getWidth()
	{
		return PLATFORM_WIDTH;
	}

	int getHeight()
	{
		return PLATFORM_HEIGHT;
	}

	SDL_Texture* getTexture()
	{
		return texture;
	}

protected:

	SDL_Texture* texture;

private:

	int x, y;
	
};

class SolidPlatform : public Platform {

public:

	SolidPlatform(int y);

	void handleJump(JumpGame* game);
	void updateAndDraw(JumpGame* game);
};

class CloudPlatform : public Platform {

public:

	CloudPlatform(int y);

	void handleJump(JumpGame* game);
	void updateAndDraw(JumpGame* game);

private:
	bool jumped = false;
	int currentFrame = 0;

	const int fadeTime = 100;
};