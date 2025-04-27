
#include "Enemy.h"
#include "BaseObject.h"
#include "CommonFunc.h"
#include "Bullet.h"

Enemy::Enemy()
{
	width_frame = 0;
	height_frame = 0;
	x_pos = 0.0;
	y_pos = 0.0;
	x_val = 0.0;
	y_val = 0.0;
	frame = 0;
	frameDelay = 200;
	lastFrameTime = 0;
	health = 15;
}

Enemy::~Enemy()
{

}

bool Enemy::LoadImg(std::string path, SDL_Renderer* render)
{
	bool ret = BaseObject::LoadImg(path, render,1);
	if (ret)
	{
		width_frame = 96;
		height_frame = 96;

	}
	return ret;
}

void Enemy::set_clips()
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

		frame_clip[3].x = width_frame * 3;
		frame_clip[3].y = 0;
		frame_clip[3].w = width_frame;
		frame_clip[3].h = height_frame;
	}
}

void Enemy::Show(SDL_Renderer* render)
{
	if (SDL_GetTicks() - lastFrameTime > frameDelay) {
		rect_.x = x_pos;
		rect_.y = y_pos;
		
		frame = (frame + 1) % 4;
		lastFrameTime = SDL_GetTicks();
	}
	width_frame = 96*1.5 ;
	height_frame = 96*1.5;
	SDL_Rect* currentClip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame, height_frame };
	SDL_RenderCopy(render, p_object, currentClip, &renderQuad);

	/*SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	SDL_RenderDrawRect(render, &rect_);*/
}

void Enemy::Update(float scroll_speed, float deltaTime)
{
	
	y_pos += scroll_speed* deltaTime;
	rect_.y = static_cast<int>(y_pos);
	
}

void Enemy::takeDamage(int damage)
{
	health -= damage;
}
