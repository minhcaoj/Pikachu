#ifndef MENU_UI_H
#define MENU_UI_H

#include <SDL.h>

class MenuUI {
public:
    MenuUI(SDL_Renderer* renderer);
    ~MenuUI();

    void RenderMenu(int mouseX, int mouseY);
    SDL_Rect playButton;
	SDL_Rect optionButton;
	SDL_Rect quitButton;
	SDL_Rect creditsButton;
	

private:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    SDL_Texture* playNormal;
    SDL_Texture* playHover;
	SDL_Texture* optionNormal;
	SDL_Texture* optionHover;
	SDL_Texture* quitNormal;
	SDL_Texture* quitHover;
	SDL_Texture* creditsNormal;
	SDL_Texture* creditsHover;
};

#endif
