#include "CommonFunc.h"
#include "Itachi.h"
#include "BaseObject.h"

SDL_Rect spriteClips[NUM_FRAMES];


std::vector<SDL_Texture*> frames;

void Itachi::LoadFrames(SDL_Renderer* renderer) {
	for (int i = 1; i < FRAME_COUNT + 1; i++) {
		char filename[50];
		sprintf_s(filename, sizeof(filename), "res/Itachi p2 fight/%d.png", i);

		SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
		if (texture) frames.push_back(texture);
	}
}

void Itachi:: RenderItachiAnimation(SDL_Renderer* renderer, int x, int y) {
	static int currentFrame = 0;
	static Uint32 lastTime = 0;

	Uint32 now = SDL_GetTicks();
	if (now - lastTime >= FRAME_DELAY) {  // Đổi frame sau FRAME_DELAY ms
		if (!frames.empty()) {  // Kiểm tra nếu frames có dữ liệu
			currentFrame = (currentFrame + 1) % frames.size();
		}

		lastTime = now;
	}

	SDL_Rect dstRect = { x, y, 300, 300 };  // Vị trí hiển thị nhân vật
	SDL_RenderCopy(renderer, frames[currentFrame], NULL, &dstRect);
}

void Itachi::FreeFrames() {
	for (SDL_Texture* tex : frames) {
		SDL_DestroyTexture(tex);
	}
	frames.clear();
}