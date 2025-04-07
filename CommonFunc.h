#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm> 

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent;
static TTF_Font* gFont = NULL;

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

const int RENDER_DRAW_COLOR = 0xff;


const int FRAME_WIDTH = 32;   // Each frame width
const int FRAME_HEIGHT = 32;  // Frame height
const int NUM_FRAMES = 4;     // Total number of frames



const int FRAME_COUNT = 18;  // Số frame trong animation
const int FRAME_DELAY = 100;

typedef struct Input
{
	int left;
	int right;
};

// Animation control
namespace SDLCommonFunc {
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	
}




