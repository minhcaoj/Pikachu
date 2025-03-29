#include "CommonFunc.h"
#include "BaseObject.h"
#include "Itachi.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


// Global variables

const int FRAME_DELAY_GAME = 1000 / 60;  // 60 FPS

Uint32 frameStart;
int frameTime;

int x = SCREEN_WIDTH / 2 - 30;  // Player position
int y = 550;
int frame = 0;
float scaleFactor = 2.0f;

Uint32 lastFrameTime = 0;
const int frameDelay = 200;   // Time (ms) per frame
const int speed = 2;
Uint32 lastTime = SDL_GetTicks();

BaseObject gBackground;
SDL_Texture* PlayerStanding;
Itachi loadItachi;

Bullet Pokeball;
Enemy enemy;





std::vector<Enemy*> MakeEnemyList()
{
    std::vector<Enemy*> list_enemy;
    Enemy* enemy_objs = new Enemy[2];

    for (int i = 0; i < 2; i++)
    {
        Enemy* p_enemy = enemy_objs + i;
        if (p_enemy != NULL)
        {
            p_enemy->LoadImg("res/Pokemon/Fire + stone dragon/sprite9_idle.png", gRenderer);
            p_enemy->set_clips();
            p_enemy->set_x_pos((SCREEN_WIDTH / 2 -110) + 140*i);
            p_enemy->set_y_pos(250);

            list_enemy.push_back(p_enemy);
        }
    }
    return list_enemy;
}

bool Init()
{
    bool success = true;
    int ret = IMG_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        success = false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    gWindow = SDL_CreateWindow("C++ SDL2 game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        success = false;
    }
    else
    {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (gRenderer == NULL) {
            success = false;
        }
        else {
            SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags)) {
                success = false;
            }
        }
    }
    return success;
}

void close()
{
    gBackground.Free();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool loadBackground()
{
    bool ret = gBackground.LoadImg("res/Grass-map1.png", gRenderer);
    if (ret == false) return false;
    return true;
}



// Main
int main(int argv, char* argc[]) {
    if (Init() == false) return -1;
    if (loadBackground() == false) return -1;
 
   
    Player p_player;
    p_player.LoadImg("res/player-sheet.png", gRenderer);
    p_player.set_clips();

    std::vector<Enemy*> enemy_lists = MakeEnemyList();
    //loadItachi.LoadFrames(gRenderer);
    bool gameStop = false;
    while (!gameStop) {

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                gameStop = true;
            }
            
            p_player.HandleInputAction(gEvent, gRenderer);
        }
        
   
        p_player.Update(deltaTime);
        p_player.HandleBullet(gRenderer);


    

       

    

        SDL_RenderClear(gRenderer);
        SDL_Delay(16);
        gBackground.Render(gRenderer, NULL);
        
       // enemy.RenderEnemies(gRenderer);
         
       // enemy.SpawnEnemy(400, 150, 2, gRenderer);// Kẻ địch trung bình
       
        p_player.Show(gRenderer);
       

        for (int i = 0; i < enemy_lists.size();i++)
        {
            Enemy* p_enemy = enemy_lists.at(i);
            if (p_enemy != NULL)
            {
                p_enemy->Show(gRenderer);
            }
        }

       

        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY_GAME) {
            SDL_Delay(FRAME_DELAY_GAME - frameTime);
        }
    }
    
    loadItachi.FreeFrames();
    close();
    return 0;
}
