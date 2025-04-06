#include "CommonFunc.h"
#include "BaseObject.h"
#include "Chest.h"

Chest::Chest()
{
	float x_pos = 0.0f;
	float y_pos = 0.0f;
	int weight_frame = 0;
	int height_frame = 0;
	bool is_close = true;
	bool is_move = true;

}

Chest::~Chest()
{

}

bool Chest::LoadImg(std::string path, SDL_Renderer* render)
{
	bool ret = BaseObject::LoadImg(path, render, 1);
	if (ret)
	{
		width_frame = 96;
		height_frame = 96;

	}
	return ret;
}
