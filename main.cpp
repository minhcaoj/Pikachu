#include "CommonFunc.h"
#include "BaseObject.h"
#include "Itachi.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "InfiniteMap.h"
#include "Collision.h"
#include "Chest.h"
#include "TextObject.h"
// Global variables

const int FRAME_DELAY_GAME = 1000 / 60;  // 60 FPS

Uint32 frameStart;
int frameTime;

float scroll_speed = 90.0f;

int x = SCREEN_WIDTH / 2 - 30;  // Player position
int y = 550;
int frame = 0;
float scaleFactor = 2.0f;

Uint32 lastFrameTime = 0;
const int frameDelay = 200;   // Time (ms) per frame
const int speed = 2;
float lastTime = SDL_GetTicks() / 1000.0f;
float lastSpawnTime = 0.0f;
float lastChestSpawnTime = 0.0f;
//player Colliding
bool isColliding = false;


Uint32 lastDamageTime = 0;
Uint32 damageCooldown = 2000;

BaseObject gBackground;
SDL_Texture* PlayerStanding;
Itachi loadItachi;

Bullet Pokeball;
Enemy enemy;

TTF_Font* fontScore = NULL;
TTF_Font* fontEnemyHealth = NULL;
TTF_Font* fontPlayerHealth = NULL;

std::vector<Enemy*> MakeEnemyList()
{
    
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

std::vector<Chest*> MakeChestList()
{
    
    std::vector<Chest*> list_chest;
    Chest* objs_chest = new Chest();


    for (int i = 0; i < list_chest.size(); i++)
    {
        Chest* p_chest= objs_chest + i;
        if (p_chest != NULL)
        {
            
            p_chest->LoadImg("res/Chest-open.png", gRenderer);
            p_chest->set_clips();
            p_chest->set_x_pos((rand() % 2) ? 250 : 350);
            p_chest->set_y_pos(-50);


            list_chest.push_back(p_chest);
        }
    }


    return list_chest;
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
		if (TTF_Init() == -1) {
			success = false;
		}
		fontScore = TTF_OpenFont("font/dlxfont_.ttf", 20);
		fontEnemyHealth = TTF_OpenFont("font/dlxfont_.ttf", 20);
		fontPlayerHealth = TTF_OpenFont("font/dlxfont_.ttf", 20);
		if (fontScore == NULL)
		{
			std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
			success = false;
		}
        if (fontEnemyHealth == NULL)
        {
			std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
			success = false;
		}
        if (fontPlayerHealth == NULL)
        {
			std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
			success = false;
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
    std::vector<Chest*> chest_lists = MakeChestList();
    

    InfiniteScrollingMap map(gRenderer, "res/Grass-map-1.png", "res/Grass-map-2.png");

    
    
    // Text

    TextObject score_game;
	TextObject player_health;
    TextObject enemy_health;
    
	score_game.SetColor(TextObject::WHITE_TEXT);
	player_health.SetColor(TextObject::WHITE_TEXT);
	enemy_health.SetColor(TextObject::WHITE_TEXT);

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
            p_enemy->set_x_pos((rand() % 2) ? 220 : 350);
            p_enemy->set_y_pos(-100);


            enemy_lists.push_back(p_enemy);
            
        }
             lastSpawnTime = currentTime;
        }
        
        if (currentTime - lastChestSpawnTime >= 5000) {
            Chest* p_chest = new Chest();
            if (p_chest != NULL)
            {
                p_chest->LoadImg("res/Chest-open.png", gRenderer);
                p_chest->set_clips();
                p_chest->set_x_pos((rand() % 2) ? 220 : 380);
                p_chest->set_y_pos(-32);


                chest_lists.push_back(p_chest);

            }
            lastChestSpawnTime = currentTime;
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
                p_enemy->Update(scroll_speed, deltaTime);
                if (p_enemy->get_y_pos() > SCREEN_HEIGHT)
                {
                    enemy_lists.erase(enemy_lists.begin() + i);
                    
                }
            }
        }
        // Spawn chest
        for (int i = 0; i < chest_lists.size();i++)
        {

            Chest* p_chest = chest_lists.at(i);

            if (p_chest != NULL)
            {
                p_chest->Chest_open_show(gRenderer, deltaTime);
                p_chest->Update(scroll_speed, deltaTime);
                if (p_chest->get_y_pos() > SCREEN_HEIGHT)
                {
                    chest_lists.erase(chest_lists.begin() + i);
                    
                }
            }
        }
        std::vector<bool> chestCollisionStates(chest_lists.size(), false);
        // 4. Player và đạn
        p_player.HandleBullet(gRenderer);
        p_player.Show(gRenderer);
        
        // Debug: in số lượng quái hiện có
        /*std::cout << "Enemies count: " << spawnManager.GetEnemies().size() << std::endl;*/

        std::vector<Bullet*> bullet_lists = p_player.get_bullet_list();
        SDL_Rect pRect = p_player.GetRect();
        SDL_Rect eRect;
        
		// Bullet and enemy collide
        for (int i = 0; i < enemy_lists.size(); i++)
        {
            
            Enemy* p_enemy = enemy_lists.at(i);
            if (p_enemy )
            {
                eRect.x = p_enemy->GetRect().x;
                eRect.y = p_enemy->GetRect().y;
                eRect.w = p_enemy->get_width_frame();
                eRect.h = p_enemy->get_height_frame();
                eRect.w *= 1.5;
                eRect.h *= 1.5;
                


                for (int t = 0; t < bullet_lists.size(); t++)
                {
                    Bullet* p_bullet = bullet_lists.at(t);
                    if (p_bullet && p_bullet->get_is_move())
                    {
                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, eRect);
                        if (bCol)
                        {
                            float damage = p_bullet->get_damage_val();
                            p_enemy->takeDamage(damage); 
                            p_bullet->set_is_move(false); // stop bullet
                            std::cout << "Hit enemy! Damage: " << damage << std::endl;

                            for (auto it = enemy_lists.begin(); it != enemy_lists.end();) {
                                Enemy* p_enemy = *it;
                                if (p_enemy->get_health() <= 0) {
                                    it = enemy_lists.erase(it); // Xóa và cập nhật iterator
                                }
                                else {
                                    ++it;
                                }
                            }

                            break; // only hit one enemy per bullet
                        }
                    }
                }
                // Player and enemies collide
                bool pCol = SDLCommonFunc::CheckCollision(pRect, eRect);
                if (pCol && !isColliding && (currentTime - lastDamageTime >= damageCooldown))
                {
                    isColliding = true;
                    float damage = p_enemy->get_health();
                    p_player.takeDamage(damage);
                    enemy_lists.erase(enemy_lists.begin() + i);
                    lastDamageTime = currentTime;
                    std::cout << "Player health: "<< p_player.get_health_val() << std::endl;
                    if (p_player.get_health_val() <= 0)
                    {
                        std::cout << "GAME OVER" << std::endl;
                    }
                }
                else if (!pCol && isColliding)
                {
                    isColliding = false;
                }
            
            }
        }

        // Player and Chest collide
        for (int r = 0; r < chest_lists.size(); r++)
        {
            Chest* p_chest = chest_lists.at(r);
            if (p_chest)
            {

                SDL_Rect cRect;
                cRect.x = p_chest->get_x_pos();
                cRect.y = p_chest->get_y_pos();
                cRect.w = p_chest->get_height_frame();
                cRect.h = p_chest->get_width_frame();
                cRect.w *= 2;
                cRect.h *= 2;
                bool pCol2 = SDLCommonFunc::CheckCollision(pRect, cRect);
                //std::cout << "Player and Chest collide" << std::endl;
                bool cCol = SDLCommonFunc::CheckCollision(cRect, eRect);
                if (cCol)
                {
                    chest_lists.erase(chest_lists.begin() + r);
                    r--;
                }
                else {
                    if (pCol2 && !chestCollisionStates[r] && (currentTime - lastDamageTime >= damageCooldown))
                    {
                        chestCollisionStates[r] = true;
                        std::cout << "Chest " << r << " and Player collide" << std::endl;
                        lastDamageTime = currentTime;
                        if (!p_chest->get_is_open()) {

                            std::cout << "Is Open" << std::endl;
                            p_chest->Open();




                        }
                    }
                    else if (!pCol2 && chestCollisionStates[r])
                    {
                        chestCollisionStates[r] = false;
                    }
                }


            }
        }

        //Show score
        std::string str_score = "Score: ";
		Uint32 score_val = SDL_GetTicks() / 1000;
	
			std::string str_val = std::to_string(score_val);
			str_score += str_val;

			score_game.setText(str_score);
			score_game.loadFromRenderText(fontScore, gRenderer);
			score_game.RenderText(gRenderer, SCREEN_WIDTH / 2 - 90 , 10);
        
			// Show player health
			std::string str_player_health = std::to_string(p_player.get_health_val() - 1);
            player_health.setText(str_player_health);
            player_health.loadFromRenderText(fontPlayerHealth, gRenderer);
			player_health.RenderText(gRenderer, p_player.GetRect().x + 13, p_player.GetRect().y - 32);
			// Show enemy health
            for (int i = 0; i < enemy_lists.size(); i++)
            {

                Enemy* p_enemy = enemy_lists.at(i);
                if (p_enemy)
                {
                    std::string str_enemy_health = std::to_string(p_enemy->get_health());
                    enemy_health.setText(str_enemy_health);
                    enemy_health.loadFromRenderText(fontEnemyHealth, gRenderer);
                    enemy_health.RenderText(gRenderer, p_enemy->GetRect().x + 40, p_enemy->GetRect().y + 140);
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
