#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"

class Itachi : public BaseObject
{
public:
	Itachi() { ; }
	~Itachi() { ; }
	void LoadFrames(SDL_Renderer* renderer);
	void RenderItachiAnimation(SDL_Renderer* renderer, int x, int y);
	void FreeFrames();
	
};