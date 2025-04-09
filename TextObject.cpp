#include "CommonFunc.h"	
#include "TextObject.h"	

TextObject::TextObject()
{
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	texture = NULL;
}

TextObject::~TextObject()
{

}

bool TextObject::loadFromRenderText(TTF_Font* font, SDL_Renderer* render)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	if (text_surface)
	{
		texture = SDL_CreateTextureFromSurface(render, text_surface);
		width = text_surface->w;
		height = text_surface->h;

		SDL_FreeSurface(text_surface);

	}
	return texture != NULL;
}

void TextObject::Free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void TextObject::SetColor(int type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255, 0 , 0 };
		text_color = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255, 255 , 255 };
		text_color = color;
	}
	else if (type == BLACK_TEXT)
	{
		SDL_Color color = { 0, 0 , 0 };
		text_color = color;
	}
}

void TextObject::RenderText(SDL_Renderer* render,
	int xp, int yp, double angle,
	SDL_Rect* clip,
	SDL_Point* center,
	SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { xp, yp, width, height };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(render, texture, clip, &renderQuad, angle, center, flip);
}
void TextObject:: renderHealth(SDL_Renderer* renderer, int health, SDL_Rect objectRect, TTF_Font* font) {
	SDL_Color white = { 255, 255, 255, 255 };
	std::string healthText = std::to_string(health);

	int textX = objectRect.x + (objectRect.w / 2) - 10; // Vị trí giữa dưới chân object
	int textY = objectRect.y + objectRect.h + 5;        // Phía dưới object

	RenderText(renderer, textX, textY);
}