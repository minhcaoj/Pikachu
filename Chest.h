#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Player.h"

#define CHEST_FRAME_NUM 3

enum ChestType {
	CHEST_FIRE_RATE = 0,
	CHEST_MOVE_SPEED = 1,
	
	HEALTH_UPGRADE = 2,
	BULLET_DAMAGE = 3,
	TROLL = 4,
};

class Chest:public BaseObject
{
public:
	Chest();
	~Chest();

	float get_x_pos() const { return x_pos; }	
	float get_y_pos() const { return y_pos; }
	int get_width_frame() const { return width_frame; }
	int get_height_frame() const { return height_frame; }
	bool get_is_open() const { return is_open; }

	void set_x_pos(const float& xPos) { x_pos = xPos; }
	void set_y_pos(const float& yPos) { y_pos = yPos; }


	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer* render);
	void Update(float scroll_speed, float deltaTime);
	void Show(SDL_Renderer* render);
	void Chest_open_show(SDL_Renderer* render, Uint32 deltaTime);
	void Open();

	void SetType(ChestType type) { chest_type = type; }
	ChestType GetType() const { return chest_type; }

	void ApplyEffectToPlayer(Player& player);

private:

	float x_pos;
	float y_pos;
	int frame;
	int width_frame;
	int height_frame;
	SDL_Rect frame_clip[CHEST_FRAME_NUM];
	Uint32 lastFrameTime;
	int frameDelay;
	bool is_open;
	ChestType chest_type;
	int scale;
	float frameTime;
	int currentFrame;
	
};
