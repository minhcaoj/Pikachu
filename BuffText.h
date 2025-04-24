#ifndef BUFFTEXT_H
#define BUFFTEXT_H

#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

class BuffText {
public:
    BuffText(std::string text, int x, int y, SDL_Color color, TTF_Font* font);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    bool isExpired() const;

private:
    std::string text_;
    SDL_Rect position_;
    SDL_Texture* texture_;
    float lifetime_;
    float totalTime_;
    float y_velocity_;
};

#endif
