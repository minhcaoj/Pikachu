#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();
	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() const { return p_object; }

	virtual bool LoadImg(std::string path, SDL_Renderer* screen, float scaleFactor);
	virtual void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

	SDL_Rect rect_;
	SDL_Texture* p_object;
};

#endif

