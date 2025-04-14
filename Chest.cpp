#include "CommonFunc.h"
#include "BaseObject.h"
#include "Chest.h"

Chest::Chest()
{
	x_pos = 0.0f;
	y_pos = 0.0f;
	width_frame = 0;
	height_frame = 0;
	is_open = false;
	frameDelay = 100;
	frameTime = 0.0f;
	currentFrame = 0;
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

	void Chest::Chest_open_show(SDL_Renderer* render, Uint32 deltaTime) {
		if (is_open) {
			if (SDL_GetTicks() - lastFrameTime > frameDelay) {
				currentFrame++;
				lastFrameTime = SDL_GetTicks();
			}
			
			// Giới hạn currentFrame từ 0 đến 2 (tối đa 3 frame)
			if (currentFrame > 2) {
				currentFrame = 2;  // Đảm bảo không vượt quá số frame hiện có
			}
		}
		else {
			currentFrame = 0;  // Nếu chưa mở, luôn hiển thị frame "đóng"
		}

		rect_.x = x_pos;
		rect_.y = y_pos;
		width_frame = 32 * scale;
		height_frame = 32 * scale;
		SDL_Rect* currentClip = &frame_clip[currentFrame];
		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame, height_frame};
		SDL_RenderCopy(render, p_object, currentClip, &renderQuad);

		//SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		//SDL_RenderDrawRect(render, &renderQuad);// Set color to black
	}


	void Chest::Open() {
		if (!is_open) {
			is_open = true;
			currentFrame = 0;
			frameTime = 0;
		}
	}

void Chest::Update(float scroll_speed, float deltaTime)
{
	y_pos += scroll_speed*deltaTime;
	rect_.y = static_cast<int>(y_pos);
	
}

void Chest::Show(SDL_Renderer* render)
{
	rect_.x = x_pos;
	rect_.y = y_pos;
	
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame*scale, height_frame*scale };
	SDL_RenderCopy(render, p_object, NULL, &renderQuad);
}