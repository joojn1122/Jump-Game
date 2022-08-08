#include "FontRenderer.hpp"
#include "RenderWindow.hpp"

FontRenderer::FontRenderer(std::string font_name, int size)
{
	std::string path = "res/fonts/" + font_name;
	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	this->font = font;

	if (font == NULL) {
		std::cout << "Font is null! " << TTF_GetError() << "\n";
	}

	FONT_HEIGHT = TTF_FontHeight(font);
}
/*
   Params: Text, width_pointer -> so the width will be passed into that var, height_pointer etc.
   You can also pass NULL as pointer
*/
void FontRenderer::getTextSize(std::string text, int* width_pointer, int* height_pointer)
{
	TTF_SizeUTF8(font, text.c_str(), width_pointer, height_pointer);
}

// returns string width
int FontRenderer::renderText(std::string text, int x, int y, SDL_Color color) {

	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(font, text.c_str(), color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(RenderWindow::getInstance().getRenderer(), surfaceMessage);
	
	int textSize = surfaceMessage->w;

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = textSize;
	rect.h = FONT_HEIGHT;

	SDL_RenderCopy(RenderWindow::getInstance().getRenderer(), texture, NULL, &rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(texture);

	return textSize;
};