#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bullet.h"

#define ENEMY_FRAME_NUM 4

class Enemy : public BaseObject
{
public:
	Enemy();
	~Enemy();

	void set_x_val(const float& xVal) { x_val = xVal; }
	void set_y_val(const float& yVal) { y_val = yVal; }

	void set_x_pos(const float& xPos) { x_pos = xPos; }
	void set_y_pos(const float& yPos) { y_pos = yPos; }

	float get_x_pos() const { return x_pos; }
	float get_y_pos() const { return y_pos; }
	
	void set_health_val(const float& healthVal) { health = healthVal; }
	float get_health() const { return health; }

	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer* render);
	void Show(SDL_Renderer* render);
	int get_width_frame() const { return width_frame; }
	int get_height_frame() const { return height_frame; }

	void Update(float scroll_speed);
	void takeDamage(std::vector<Enemy*> enemy, std::vector<Bullet*> bullet, float damage);


private:
	float x_val;
	float y_val;
	float x_pos;
	float y_pos;
	int frame;
	int width_frame;
	int height_frame;
	SDL_Rect frame_clip[ENEMY_FRAME_NUM];
	Uint32 lastFrameTime;
	int frameDelay;
	float health;

};