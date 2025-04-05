#include "CommonFunc.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
    // Kiểm tra từng cạnh
    bool x_overlap = (a.x <= b.x + b.w) && (a.x >= b.x);
    bool y_overlap = (a.y <= b.y + b.h) && (a.y + a.h >= b.y);

    bool collision = x_overlap && y_overlap;

    

    return collision;
}