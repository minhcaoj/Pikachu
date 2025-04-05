#include "CommonFunc.h"
#include "Bullet.h"

Bullet::Bullet()
{
    x_val = 0;
    y_val = 0;
    is_move = false;
    damage = 5.0f;
}



Bullet::~Bullet() {

}

void Bullet::HandleMove()
{
    rect_.y -= y_val;
    if (rect_.y < 0)
    {
        is_move = false;
    }
}

bool Bullet::LoadImg(std::string path, SDL_Renderer* render, float scaleFactor) {
    return BaseObject::LoadImg(path, render, scaleFactor);
}
