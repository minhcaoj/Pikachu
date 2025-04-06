#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"

#define CHEST_FRAME_NUM 3

class Chest:public BaseObject
{
public:
	Chest();
	~Chest();

	float get_x_pos() const { return x_pos; }	
	float get_y_pos() const { return y_pos; }
	int get_width_frame() const { return width_frame; }
	int get_height_frame() const { return height_frame; }


	void set_x_pos(const float& xPos) { x_pos = xPos; }
	void set_y_pos(const float& yPos) { y_pos = yPos; }

	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer* render);
	void Update(float scroll_speed);
	void Show(SDL_Renderer* render);
	void Chest_open_show(SDL_Renderer* render);
	

private:
	float x_val;
	float y_val;
	float x_pos;
	float y_pos;
	int frame;
	int width_frame;
	int height_frame;
	SDL_Rect frame_clip[CHEST_FRAME_NUM];
	Uint32 lastFrameTime;
	int frameDelay;
	bool is_close;
	bool is_move;
	int scale;
};
