#include "CommonFunc.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
    // Kiểm tra từng cạnh
    bool x_overlap = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlap = (a.y < b.y + b.h) && (a.y + a.h > b.y);

    bool collision = x_overlap && y_overlap;

    // Debug chi tiết
    std::cout << "Collision between: "
        << "A(" << a.x << "," << a.y << ")-(" << a.w << "x" << a.h << ") "
        << "B(" << b.x << "," << b.y << ")-(" << b.w << "x" << b.h << ") "
        << "Result: " << collision
        << " (X: " << x_overlap << " Y: " << y_overlap << ")\n";

    return collision;
}