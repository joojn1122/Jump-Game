#include "RenderWindow.hpp"
#include "FontRenderer.hpp"
#include <iostream>


RenderWindow::RenderWindow(const char* name, int width, int height, int flags)
	:width(width), height(height)
{
	if (
		SDL_Init(SDL_INIT_EVERYTHING) == 0
		&& IMG_Init(IMG_INIT_PNG)
		&& TTF_Init() != -1
	) 
	{
		std::cout << "Subsystems Initialized!\n";

		window = SDL_CreateWindow("Jump Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window) {
			std::cout << "Window Created!\n";
			SDL_SetWindowMinimumSize(window, 100, 100);
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer)
		{
			std::cout << "Renderer created!\n";
			//SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
			//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			isRunning = true;
		}
	}
}

void RenderWindow::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:

			isRunning = false;
			break;

		case SDL_KEYDOWN:
			
			if (!this->keyPressed(event.key.keysym.sym))
			{
				this->pressed_keys.push_back(event.key.keysym.sym);
			}

			break;

		case SDL_KEYUP:

			this->removeKey(event.key.keysym.sym);

			break;

		case SDL_MOUSEBUTTONDOWN:
			
			if (!this->mouseClicked(event.button.button))
			{
				this->clicks.push_back(event.button.button);
			}

			break;

		case SDL_MOUSEBUTTONUP:

			this->removeClick(event.button.button);

			break;

		default:
			break;
	}
}

SDL_Texture* RenderWindow::loadTexture(std::string file_name)
{
	std::string folder = "res/images/" + file_name;
	
	return IMG_LoadTexture(renderer,
		folder.c_str());
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::draw(int x, int y, int width, int height, int textureX, int textureY, int textureWidth, int textureHeight, SDL_Texture* texture)
{
	SDL_Rect src;
	src.x = textureX;
	src.y = textureY;
	src.w = textureWidth;
	src.h = textureHeight;

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::draw(int x, int y, int width, int height, SDL_Texture* texture)
{
	int h;
	this->getWindowSize(NULL, &h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = h - height - y; // drawing from bottom
	dst.w = width;
	dst.h = height;

	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

/*
	or 
	class RenderWindow
	{ 
		void destroy(){
		  ...
		}
	}
*/
void RenderWindow::destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex( window );
	
	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);
	
	return mode.refresh_rate;
}

void RenderWindow::getWindowSize(int* w_pointer, int* h_pointer)
{
	SDL_GetWindowSize(window, w_pointer, h_pointer);
}

void RenderWindow::removeKey(int key)
{
	for (int i = 0; i < pressed_keys.size(); i++)
	{
		int k = pressed_keys[i];
		
		if (k == key)
		{
			pressed_keys.erase(pressed_keys.begin() + i);
			break;
		}
	}
}

bool RenderWindow::keyPressed(int key)
{

	for (int i = 0; i < pressed_keys.size(); i++)
	{
		int k = pressed_keys[i];

		if (key == k)
		{
			return true;
		}
	}

	return false;
}

void RenderWindow::removeClick(int key)
{
	for (int i = 0; i < clicks.size(); i++)
	{
		int k = clicks[i];

		if (k == key)
		{
			clicks.erase(clicks.begin() + i);
			break;
		}
	}
}

bool RenderWindow::mouseClicked(int key)
{

	for (int i = 0; i < clicks.size(); i++)
	{
		int k = clicks[i];

		if (key == k)
		{
			return true;
		}
	}

	return false;
}

void RenderWindow::drawSquare(int x, int y, int width, int height, SDL_Color color)
{
	int h;
	getWindowSize(NULL, &h);

	SDL_Rect rect = {
		x, h - height - y,
		width, height
	};

	// set black color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
	if (color.a < 255)
	{
		SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
	}

	if (SDL_RenderFillRect(this->renderer, &rect) < 0) 
	{
		std::cout << "Error happened " << SDL_GetError() << "\n";
	}
}