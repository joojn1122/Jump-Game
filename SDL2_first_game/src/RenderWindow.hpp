#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include <vector>

class GuiScreen;

class RenderWindow {
public:
	RenderWindow(const char* name, int width, int height, int flags);

	SDL_Texture* loadTexture(std::string file_name);
	void draw(int x, int y, int width, int height, SDL_Texture* texture);
	void draw(int x, int y, int width, int height, int textureX, int textureY, int textureWidth, int textureHeight, SDL_Texture* texture);

	int getRefreshRate();

	void clear();
	void display();

	void handleEvents();
	void destroy();

	inline SDL_Renderer* getRenderer()
	{
		return renderer;
	}

	void getWindowSize(int* w_pointer, int* h_pointer);

	bool isRunning;
	int width;
	int height;

	void removeKey(int key);
	void removeClick(int key);
	bool keyPressed(int key);
	bool mouseClicked(int key);

	static RenderWindow& getInstance()
	{
		static RenderWindow INSTANCE("Jump Game", 600, 700, SDL_WINDOW_RESIZABLE);

		return INSTANCE;
	}

	GuiScreen* currentScreen; 

	void drawSquare(int x, int y, int width, int height, SDL_Color color);

private:
	// pointer so it's not inicialized
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	std::vector<int> pressed_keys;
	std::vector<int> clicks;
};
