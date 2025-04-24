#include "BuffText.h"

BuffText::BuffText(std::string text, int x, int y, SDL_Color color, TTF_Font* font)
    : text_(text), texture_(nullptr), lifetime_(1.5f), totalTime_(0.0f), y_velocity_(-30.0f) {

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    texture_ = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)), textSurface);

    position_.x = x;
    position_.y = y;
    position_.w = textSurface->w;
    position_.h = textSurface->h;

    SDL_FreeSurface(textSurface);
}

void BuffText::update(float deltaTime) {
    totalTime_ += deltaTime;
    position_.y += static_cast<int>(y_velocity_ * deltaTime); // Bay lên
}

void BuffText::render(SDL_Renderer* renderer) {
    if (texture_) {
        SDL_RenderCopy(renderer, texture_, nullptr, &position_);
    }
}

bool BuffText::isExpired() const {
    return totalTime_ > lifetime_;
}
