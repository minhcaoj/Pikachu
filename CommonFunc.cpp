#include "CommonFunc.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
 

    

	return SDL_HasIntersection(&a, &b);
}


