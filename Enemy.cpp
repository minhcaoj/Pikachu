
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
	SDL_Rect* currentClip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame, height_frame };
	SDL_RenderCopy(render, p_object, currentClip, &renderQuad);
}

void Enemy::Update(float scroll_speed)
{
	
	y_pos += scroll_speed;
	rect_.y = static_cast<int>(y_pos);
	if (y_pos > SCREEN_HEIGHT)
	{

	}
}

void Enemy::takeDamage(std::vector<Enemy*> enemy, std::vector<Bullet*> bullet, float damage)
{
	std::vector<float> enemy_health_val;
	for (int i = 0; i < enemy.size(); i++)
	{
		Enemy* p_enemy = enemy.at(i);
		if (enemy_health_val.at(i) == NULL) {
			enemy_health_val.push_back(p_enemy->get_health());
		}
		if (p_enemy)
		{
			
				for (int t = 0; t < bullet.size(); t++)
				{
					Bullet* p_bullet = bullet.at(t);
					if (p_bullet)
					{

						damage = p_bullet->get_damage_val();
						enemy_health_val.at(i) -= damage;
						if (enemy_health_val.at(i) <= 0)
						{
							enemy.erase(enemy.begin() + i);
						}
					}
				}
			
			
			
			
		}
	}
}
