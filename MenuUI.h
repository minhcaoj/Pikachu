#ifndef MENU_UI_H
#define MENU_UI_H

#include <SDL.h>

class MenuUI {
public:
    MenuUI(SDL_Renderer* renderer);
    ~MenuUI();

    void RenderMenu();
    SDL_Rect playButton, optionsButton, creditsButton, quitButton;

private:
    SDL_Renderer* renderer;
    SDL_Texture* menuTexture;
};

#endif
