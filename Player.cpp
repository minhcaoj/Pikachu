#include "CommonFunc.h"
#include "Player.h"
#include "Bullet.h"
#include "BaseObject.h"


Player::Player()
{
	frame = 0;
	x_pos = SCREEN_WIDTH / 2 - 30;
	y_pos = 550;
	x_val = 0;
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	lastFrameTime = 0;
	frameDelay = 200;
	input_type.left = 0;
	input_type.right = 0;
	speed = 100.0f;
	scaleFactor = 2;
	bulletLevel = 1;
}

Player::~Player()
{

}

bool Player::LoadImg(std::string path, SDL_Renderer* render)
{
	bool ret = BaseObject::LoadImg(path, render);
	if (ret == true)
	{
		width_frame = 32;
		height_frame = 32;
	}
	return ret;
}

void Player::set_clips()
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

void Player::Show(SDL_Renderer* render)
{
	
	if (SDL_GetTicks() - lastFrameTime > frameDelay) {
		rect_.x = x_pos;
		rect_.y = y_pos;
		frame = (frame + 1) % 4;

		
		lastFrameTime = SDL_GetTicks();

		

	}

	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame*scaleFactor, height_frame*scaleFactor };
	SDL_RenderCopy(render, p_object, current_clip, &renderQuad);

}

void Player::HandleBullet(SDL_Renderer* render)
{
	for (int i = 0; i < p_bullet_list.size(); i++) // Duyệt từ cuối về đầu
	{
		Bullet* p_bullet = p_bullet_list[i];
		if (p_bullet != nullptr)
		{
			if (p_bullet->get_is_move())
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(render);
			}
			else
			{
				delete p_bullet;  // Giải phóng bộ nhớ
				p_bullet = nullptr;
				p_bullet_list.erase(p_bullet_list.begin() + i);
			}
		}
	}
}


void Player::HandleInputAction(SDL_Event events, SDL_Renderer* render) {
	if (events.type == SDL_KEYDOWN) { // Không nhận sự kiện auto-repeat
		switch (events.key.keysym.sym) {
		case SDLK_a:
			input_type.left = 1;
			break;
		case SDLK_d:
			input_type.right = 1;
			break;
		

		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
		case SDLK_a:
			input_type.left = 0;
			break;
		case SDLK_d:
			input_type.right = 0;
			break;
		default:
			break;
		}
	}
	if (events.type == SDL_MOUSEBUTTONDOWN) {
		if (events.button.button == SDL_BUTTON_LEFT) {
			Bullet* p_bullet = new Bullet();
			
			if (p_bullet != nullptr && p_bullet->LoadImg("res//Ball//poke ball.png", render)) {
				p_bullet->SetRect(this->rect_.x + width_frame - 16, rect_.y + height_frame);
				p_bullet->set_y_val(20);
				p_bullet->set_is_move(true);
				
				p_bullet_list.push_back(p_bullet);
			}
			else {
				delete p_bullet;
				p_bullet = nullptr;
			}

		}
	}

}


void Player::Update(float deltaTime) {
	float moveSpeed = speed * deltaTime;  // Tốc độ dựa vào deltaTime

	if (input_type.left) {
		if (x_pos - moveSpeed >= 200) {
			x_pos -= moveSpeed;
		}
	}
	if (input_type.right) {
		if (x_pos + moveSpeed + FRAME_WIDTH * scaleFactor <= SCREEN_WIDTH - 200) {
			x_pos += moveSpeed;
		}
	}
}
