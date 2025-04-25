#include "MenuUI.h"
#include <SDL_image.h>
#include <iostream>

MenuUI::MenuUI(SDL_Renderer* renderer) : renderer(renderer),
backgroundTexture(nullptr), playNormal(nullptr), playHover(nullptr), optionNormal(nullptr), optionHover(nullptr),
quitNormal(nullptr), quitHover(nullptr), creditsNormal(nullptr), creditsHover(nullptr) {

    backgroundTexture = IMG_LoadTexture(renderer, "res/Background_menu.png");
    playNormal = IMG_LoadTexture(renderer, "res/Menu_button/Play.png");
    playHover = IMG_LoadTexture(renderer, "res/Menu_button/Play_hover.png");
	optionNormal = IMG_LoadTexture(renderer, "res/Menu_button/Options.png");
	optionHover = IMG_LoadTexture(renderer, "res/Menu_button/Options_hover.png");
	quitNormal = IMG_LoadTexture(renderer, "res/Menu_button/Quit.png");
	quitHover = IMG_LoadTexture(renderer, "res/Menu_button/Quit_hover.png");
	creditsNormal = IMG_LoadTexture(renderer, "res/Menu_button/Credits.png");
	creditsHover = IMG_LoadTexture(renderer, "res/Menu_button/Credits_hover.png");



    // Tọa độ chính xác của nút Play trên menu
    playButton = { 190, 320, 300, 100 };
	optionButton = { 190, 420, 300, 100 };
	creditsButton = { 190, 520, 300, 100 };
	quitButton = { 190, 620, 300, 100 };
	replayButton = { 190, 420, 300, 100 };
	optionButtonOver = { 190, 520, 300, 100 };
	
	
	
	// Tạo các nút khác nếu cần
	// optionButton = { ... };
	// quitButton = { ... };
}

MenuUI::~MenuUI() {
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (playNormal) SDL_DestroyTexture(playNormal);
    if (playHover) SDL_DestroyTexture(playHover);
	if (optionNormal) SDL_DestroyTexture(optionNormal);
	if (optionHover) SDL_DestroyTexture(optionHover);
	if (quitNormal) SDL_DestroyTexture(quitNormal);
	if (quitHover) SDL_DestroyTexture(quitHover);
	if (creditsNormal) SDL_DestroyTexture(creditsNormal);
	if (creditsHover) SDL_DestroyTexture(creditsHover);
	
}

void MenuUI::RenderMenu(int mouseX, int mouseY) {
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

	SDL_Point mousePos = { mouseX, mouseY };
    SDL_Texture* playTex = SDL_PointInRect(&mousePos, &playButton)
        ? playHover : playNormal;
	SDL_Texture* optionTex = SDL_PointInRect(&mousePos, &optionButton)
		? optionHover : optionNormal;
	SDL_Texture* quitTex = SDL_PointInRect(&mousePos, &quitButton)
		? quitHover : quitNormal;
	SDL_Texture* creditsTex = SDL_PointInRect(&mousePos, &creditsButton)
		? creditsHover : creditsNormal;

    SDL_RenderCopy(renderer, playTex, nullptr, &playButton);
	SDL_RenderCopy(renderer, optionTex, nullptr, &optionButton);
	SDL_RenderCopy(renderer, quitTex, nullptr, &quitButton);
	SDL_RenderCopy(renderer, creditsTex, nullptr, &creditsButton);
	SDL_RenderPresent(renderer);
}

void MenuUI::RenderGameOver(int mouseX, int mouseY)
{
	SDL_Point mousePos = { mouseX, mouseY };
	SDL_Texture* replayTex = SDL_PointInRect(&mousePos, &replayButton)
		? playHover : playNormal;
	
	SDL_Texture* quitTex = SDL_PointInRect(&mousePos, &quitButton)
		? quitHover : quitNormal;
	SDL_Texture* OptionTex = SDL_PointInRect(&mousePos, &optionButtonOver)
		? optionHover : optionNormal;

	SDL_RenderCopy(renderer, replayTex, nullptr, &replayButton);
	SDL_RenderCopy(renderer, OptionTex, nullptr, &optionButtonOver);
	SDL_RenderCopy(renderer, quitTex, nullptr, &quitButton);
}
