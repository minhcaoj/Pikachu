#include "CommonFunc.h"
#include "BaseObject.h"
#include "Itachi.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "InfiniteMap.h"
#include "Collision.h"


// Global variables

const int FRAME_DELAY_GAME = 1000 / 60;  // 60 FPS

Uint32 frameStart;
int frameTime;

float scroll_speed = 100.0f;

int x = SCREEN_WIDTH / 2 - 30;  // Player position
int y = 550;
int frame = 0;
float scaleFactor = 2.0f;

Uint32 lastFrameTime = 0;
const int frameDelay = 200;   // Time (ms) per frame
const int speed = 2;
float lastTime = SDL_GetTicks() / 1000.0f;
float lastSpawnTime = 0.0f;

BaseObject gBackground;
SDL_Texture* PlayerStanding;
Itachi loadItachi;

Bullet Pokeball;
Enemy enemy;

std::vector<Enemy*> MakeEnemyList()
{
    Uint32 currentTime = SDL_GetTicks();
    std::vector<Enemy*> list_enemy;
    Enemy* enemy_objs = new Enemy();
    
        
    for (int i = 0; i < list_enemy.size(); i++)
    {
        Enemy* p_enemy = enemy_objs + i;
        if (p_enemy != NULL)
        {
            p_enemy->LoadImg("res/Pokemon/Fire + stone dragon/sprite9_idle.png", gRenderer);
            p_enemy->set_clips();
            p_enemy->set_x_pos((rand() % 2) ? 250 : 350);
            p_enemy->set_y_pos(-100);


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





// Main
int main(int argv, char* argc[]) {
    if (Init() == false) return -1;

    ///*EnemySpawnManager spawnManager;*/
    //spawnManager.SetRenderer(gRenderer);
    // spawnManager.LoadEnemyTexture("res/Pokemon/Fire + stone dragon/sprite9_idle.png", gRenderer, 1);
    Collision collision;
    
     Player p_player;
    p_player.LoadImg("res/player-sheet.png", gRenderer);
    p_player.set_clips();

    std::vector<Enemy*> enemy_lists = MakeEnemyList();
    
    

    InfiniteScrollingMap map(gRenderer, "res/Grass-map-1.png", "res/Grass-map-2.png");

    
    
    //loadItachi.LoadFrames(gRenderer);
    bool gameStop = false;


    // Main game loop
    while (!gameStop) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        
        lastTime = currentTime;
        if (currentTime - lastSpawnTime >= 10000) {
            Enemy* p_enemy = new Enemy();
             if (p_enemy != NULL)
        {
            p_enemy->LoadImg("res/Pokemon/Fire + stone dragon/sprite9_idle.png", gRenderer);
            p_enemy->set_clips();
            p_enemy->set_x_pos((rand() % 2) ? 250 : 350);
            p_enemy->set_y_pos(-100);


            enemy_lists.push_back(p_enemy);
            
        }
             lastSpawnTime = currentTime;
        }
        

        // Xử lý sự kiện
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) gameStop = true;
            p_player.HandleInputAction(gEvent, gRenderer);
        }

        // Cập nhật game state
        map.Update(deltaTime, scroll_speed);
        /*spawnManager.Update(deltaTime, scroll_speed);*/
        p_player.Update(deltaTime);
      
        /*enemy.SpawnEnemy(enemy, lastFrameTime);*/
        // Render (QUAN TRỌNG: thứ tự đúng)
        SDL_RenderClear(gRenderer);

        // 1. Background đầu tiên
        gBackground.Render(gRenderer, NULL);

        // 2. Map
        map.Render(gRenderer);
       /* std::cout << "Enemy count" << enemy_lists.size() << std::endl;*/
        for (int i = 0; i < enemy_lists.size();i++)
        {

            Enemy* p_enemy = enemy_lists.at(i);
           
            if (p_enemy != NULL)
            {
                p_enemy->Show(gRenderer);
                p_enemy->Update(scroll_speed / 100);
                if (p_enemy->get_y_pos() > SCREEN_HEIGHT)
                {
                    enemy_lists.erase(enemy_lists.begin() + i);
                    
                }
            }
        }
        

        // 4. Player và đạn
        p_player.HandleBullet(gRenderer);
        p_player.Show(gRenderer);
        
        // Debug: in số lượng quái hiện có
        /*std::cout << "Enemies count: " << spawnManager.GetEnemies().size() << std::endl;*/

        std::vector<Bullet*> bullet_lists = p_player.get_bullet_list();
        std::cout << "BulletSize: " << bullet_lists.size() << std::endl;
        for (int i = 0; i < bullet_lists.size(); i++)
        {
            Bullet* p_bullet = bullet_lists.at(i);
            if (p_bullet && p_bullet->get_is_move())
            {
                SDL_Rect bRect = p_bullet->GetRect();

                for (int t = 0; t < enemy_lists.size(); t++)
                {
                    Enemy* p_enemy = enemy_lists.at(t);
                    if (p_enemy)
                    {
                        SDL_Rect eRect;
                        eRect.x = p_enemy->GetRect().x;
                        eRect.y = p_enemy->GetRect().y;
                        eRect.w = p_enemy->get_width_frame();
                        eRect.h = p_enemy->get_height_frame();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, eRect);
                        if (bCol)
                        {
                            float damage = p_bullet->get_damage_val();
                            p_enemy->takeDamage(damage); // ✅ only apply damage once
                            p_bullet->set_is_move(false); // stop bullet
                            std::cout << "Hit enemy! Damage: " << damage << std::endl;

                            // Optional: remove enemy if dead
                            if (p_enemy->get_health() <= 0) {
                                enemy_lists.erase(enemy_lists.begin() + t);
                                --t; // prevent skipping next enemy
                            }

                            break; // only hit one enemy per bullet
                        }
                    }
                }
            }
        }



        SDL_RenderPresent(gRenderer);

        // Giữ ổn định FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY_GAME) {
            SDL_Delay(FRAME_DELAY_GAME - frameTime);
        }
    }
    close();
    return 0;
}
