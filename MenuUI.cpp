#include "MenuUI.h"
#include <SDL_image.h>
#include <iostream>

MenuUI::MenuUI(SDL_Renderer* renderer) : renderer(renderer), menuTexture(nullptr) {
    menuTexture = IMG_LoadTexture(renderer, "res/Monster_Adventure_Menu.png");
    if (!menuTexture) {
        std::cerr << "Failed to load menu texture: " << IMG_GetError() << std::endl;
    }

    playButton = { 190, 200, 300, 120 };
    optionsButton = { 190, 340, 300, 100 };
    creditsButton = { 190, 450, 300, 100 };
    quitButton = { 190, 560, 300, 100 };
}

MenuUI::~MenuUI() {
    if (menuTexture) {
        SDL_DestroyTexture(menuTexture);
    }
}

void MenuUI::RenderMenu() {
    SDL_RenderCopy(renderer, menuTexture, nullptr, nullptr);
}
