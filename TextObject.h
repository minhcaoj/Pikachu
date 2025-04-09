#pragma once

#include "CommonFunc.h"
class TextObject
{
public:
	TextObject();
	~TextObject();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2
	};

	bool loadFromFile(std::string path);
	bool loadFromRenderText(TTF_Font* font, SDL_Renderer* render);
	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* render,
					int xp, int yp, double angle = 0.0,
					SDL_Rect* clip = NULL, 
					SDL_Point* center = NULL, 
					SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderHealth(SDL_Renderer* renderer, int health, SDL_Rect objectRect, TTF_Font* font);

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	void setText(const std::string& text) { str_val = text; }
	std::string getText() const { return str_val; }

private:
	std::string str_val;
	SDL_Color text_color;
	SDL_Texture* texture;
	int width;
	int height;

};
