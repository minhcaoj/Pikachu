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
	frameDelay = 200;
	lastFrameTime = 0;
	frame = 0;
	scale = 3;
}

Chest::~Chest()
{

}

bool Chest::LoadImg(std::string path, SDL_Renderer* render)
{
	bool ret = BaseObject::LoadImg(path, render, 3);
	if (ret)
	{
		width_frame = 32;
		height_frame = 32;

	}
	return ret;
}

void Chest::set_clips()
{
	if (width_frame > 0 && height_frame > 0)
	{
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = width_frame;
		frame_clip[0].h = height_frame;

		frame_clip[1].x = width_frame;
		frame_clip[1].y = 0;
		frame_clip[1].w = width_frame;
		frame_clip[1].h = height_frame;

		frame_clip[2].x = width_frame * 2;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame;
		frame_clip[2].h = height_frame;
	}
}


void Chest::Chest_open_show(SDL_Renderer* render)
{
	if (SDL_GetTicks() - lastFrameTime > frameDelay) {
		rect_.x = x_pos;
		rect_.y = y_pos;
		frame = (frame + 1) % 3;
		lastFrameTime = SDL_GetTicks();
	}
	SDL_Rect* currentClip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame, height_frame };
	SDL_RenderCopy(render, p_object, currentClip, &renderQuad);
}

void Chest::Update(float scroll_speed)
{
	y_pos += scroll_speed;
	rect_.y = static_cast<int>(y_pos);
	if (y_pos > SCREEN_HEIGHT)
	{

	}
}

void Chest::Show(SDL_Renderer* render)
{
	rect_.x = x_pos;
	rect_.y = y_pos;
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame*scale, height_frame*scale };
	SDL_RenderCopy(render, p_object, NULL, &renderQuad);
}