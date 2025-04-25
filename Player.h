#ifndef PLAYER_H
#define PLAYER_H
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bullet.h"

#define PLAYER_FRAME_NUM 4
class Player : public BaseObject
{
public:
	Player();
	~Player();
	int get_health_val() const { return PlayerHealth; }
	void set_health_val(const int& player_health) { PlayerHealth = player_health; }

	float get_speed_val() const { return speed; }	
	void set_speed_val(const int& speedVal) { speed = speedVal; }
	
	bool LoadImg(std::string path, SDL_Renderer* render);
	void Show(SDL_Renderer* render);
	void HandleInputAction(SDL_Event events, SDL_Renderer* render);
	void set_clips();
	void SetSclae(float scale) { scaleFactor = scale; }
	void Update(float deltaTime);
	void HandleBullet(SDL_Renderer* render);
	void takeDamage(float damage);
	void Reset();
	SDL_Rect GetRectFrame();
	void set_bullet_lists(std::vector<Bullet*> bullet_list)
	{
		p_bullet_list = bullet_list;
	}
	std::vector<Bullet*> get_bullet_list() const { return p_bullet_list; }

	int get_bullet_damage() const { return bulletDamage; }
	void set_bullet_damage(int damage) { bulletDamage = damage; }
	int get_bullet_speed() const { return bulletSpeed; }
	void set_bullet_speed(int speed) { bulletSpeed = speed; }

private:
	std::vector<Bullet*> p_bullet_list;
	

	float x_val;
	float y_val;
	float x_pos;
	float y_pos;
	int width_frame;
	int height_frame;
	int bulletLevel;
	int maxBulletLevel = 4;
	Uint32 lastFrameTime;
	SDL_Rect frame_clip[PLAYER_FRAME_NUM];
	Input input_type;
	int frame;
	int frameDelay;
	float speed;
	int scaleFactor;
	int PlayerHealth;
	float lastTime;
	int bulletSpeed;
	int bulletDamage;
};

#endif