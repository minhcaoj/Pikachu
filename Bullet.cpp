#include "CommonFunc.h"
#include "Bullet.h"

Bullet::Bullet()
{
    x_val = 0;
    y_val = 0;
    is_move = false;
   
}


Bullet::~Bullet() {

}

void Bullet::HandleMove(const int& border_x, const int& border_y)
{
    rect_.y += y_val;
    if (y_val < border_y)
    {
        is_move = false;
    }
}

bool Bullet::LoadImg(std::string path, SDL_Renderer* render) {
    return BaseObject::LoadImg(path, render);
}
