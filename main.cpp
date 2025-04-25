
#include "BaseObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "InfiniteMap.h"
#include "Collision.h"
#include "Chest.h"
#include "TextObject.h"
#include "MenuUI.h"
#include "BuffText.h"

// Global variables

const int FRAME_DELAY_GAME = 1000 / 60;  // 60 FPS

Uint32 frameStart;
int frameTime;

float scroll_speed = 90.0f;

int x = SCREEN_WIDTH / 2 - 30;  // Player position
int y = 550;
int frame = 0;
float scaleFactor = 2.0f;
int score;

Uint32 lastFrameTime = 0;
const int frameDelay = 200;   // Time (ms) per frame
const int speed = 2;
float lastTime = SDL_GetTicks() / 1000.0f;
float lastSpawnTime = 0.0f;
float lastChestSpawnTime = 0.0f;
//player Colliding
bool isColliding = false;
bool timing = true;


Uint32 lastDamageTime = 0;
Uint32 damageCooldown = 2000;
Uint32 startTime = 0;

BaseObject gBackground;
SDL_Texture* PlayerStanding;


Bullet Pokeball;
Enemy enemy;

TTF_Font* fontScore = NULL;
TTF_Font* fontEnemyHealth = NULL;
TTF_Font* fontPlayerHealth = NULL;
TTF_Font* chestText = NULL;
TTF_Font* fontScoreOver = NULL;

std::vector<BuffText> buffTextList;
 // Khởi tạo seed cho rand()




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
        Chest* p_chest = objs_chest + i;
        if (p_chest != NULL)
        {

            p_chest->LoadImg("res/Chest-open.png", gRenderer);
            p_chest->set_clips();
            p_chest->set_x_pos((rand() % 2) ? 250 : 350);
            p_chest->set_y_pos(-50);
            /*p_chest->RandomizeType();*/
			p_chest->SetType(static_cast<ChestType>(rand() % 3));

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
		fontScoreOver = TTF_OpenFont("font/dlxfont_.ttf", 30);
		chestText = TTF_OpenFont("font/dlxfont_.ttf", 20);
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



bool isInside(SDL_Rect rect, int x, int y) {
    return (x > rect.x && x < rect.x + rect.w &&
        y > rect.y && y < rect.y + rect.h);
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
    srand(static_cast<unsigned int>(time(nullptr)));

    InfiniteScrollingMap map(gRenderer, "res/Grass-map-1.png", "res/Grass-map-2.png");

    MenuUI menu(gRenderer);
    MenuUI gameOverRender(gRenderer);


    // Text

    TextObject score_game;
    TextObject player_health;
    TextObject enemy_health;

    score_game.SetColor(TextObject::WHITE_TEXT);
    player_health.SetColor(TextObject::WHITE_TEXT);
    enemy_health.SetColor(TextObject::WHITE_TEXT);

    bool gameStop = false;
    bool inMenu = true;
    SDL_Texture* gameOverTexture = IMG_LoadTexture(gRenderer, "res/Game_over.png");
	SDL_Texture* background = IMG_LoadTexture(gRenderer, "res/Background_scene.png");

    bool gameOver = false;
    

    int mouseX = 0, mouseY = 0;
    

    // Main game loop
    while (!gameStop) {
		
        Uint32 currentTime = SDL_GetTicks();
        
        
		
        // Xử lý sự kiện
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) gameStop = true;
            else if (gEvent.type == SDL_MOUSEMOTION) {
                mouseX = gEvent.motion.x;
                mouseY = gEvent.motion.y;
            }
            else if (gEvent.type == SDL_MOUSEBUTTONDOWN && inMenu) {
                if (isInside(menu.playButton, mouseX, mouseY)) {
                    std::cout << "Play clicked!\n";
                    inMenu = false;

                }
                if (isInside(menu.quitButton, mouseX, mouseY)) {
                    std::cout << "Quit clicked!\n";
                    gameStop = true;
                }
                if (isInside(menu.creditsButton, mouseX, mouseY)) {
                    std::cout << "Credits clicked!\n";
                    // Show credits screen or perform any action you want
                }
                if (isInside(menu.optionButton, mouseX, mouseY)) {
                    std::cout << "Options clicked!\n";
                    // Show options screen or perform any action you want
                }
            }
            else if (gEvent.type == SDL_MOUSEBUTTONDOWN && gameOver) {
              
                if (isInside(gameOverRender.replayButton, mouseX, mouseY)) {
                    std::cout << "Restart clicked!\n";
                    // Reset game state
                    gameOver = false;
                    inMenu = false;
                    timing = true;
                    score = 0;
                    enemy_lists.clear();
                    chest_lists.clear();
                    p_player.Reset(); // Hàm reset trạng thái của Player
                }
				if (isInside(gameOverRender.quitButton, mouseX, mouseY)) {
					std::cout << "Quit clicked!\n";
					gameStop = true;
				}
                if (isInside(menu.optionButton, mouseX, mouseY)) {
                    std::cout << "Options clicked!\n";
                    // Show options screen or perform any action you want
                }
            }
        

            p_player.HandleInputAction(gEvent, gRenderer);
        }


        // Cập nhật game state
       

        /*enemy.SpawnEnemy(enemy, lastFrameTime);*/
        // Render (QUAN TRỌNG: thứ tự đúng)
        SDL_RenderClear(gRenderer);

        if (inMenu) {
            menu.RenderMenu(mouseX, mouseY);
            
         
        }
        
        else {
            if (timing) {
				startTime = SDL_GetTicks();
				timing = false;
            }
			
            
            if (!gameOver)
            {
                float deltaTime = (currentTime - lastTime) / 1000.0f;
                
                
				
               
				

                lastTime = currentTime;
                if (SDL_GetTicks() - startTime - lastSpawnTime >= 10000) {
					int caseEnemy = rand() % 3;
                    Enemy* p_enemy = new Enemy();
					Enemy* p_enemy1 = new Enemy();
					Enemy* p_enemy2 = new Enemy();
                    switch (caseEnemy) {
					case 0:
						// Spawn Dragon
						
                        if (p_enemy != NULL)
                        {
                            p_enemy->LoadImg("res/Pokemon/Fire + stone dragon/sprite9_idle.png", gRenderer);
                            p_enemy->set_health_val(15 + ((SDL_GetTicks() - startTime) / 1000));
                            p_enemy->set_clips();

                            p_enemy->set_x_pos((rand() % 2) ? 220 : 350);

                            p_enemy->set_y_pos(-150);


                            enemy_lists.push_back(p_enemy);

                        }
                        lastSpawnTime = currentTime;
						break;
					case 1:
                        
                        if (p_enemy != NULL)
                        {
                            p_enemy->LoadImg("res/Pokemon/Leaf - lion/sprite3_idle.png", gRenderer);
                            p_enemy->set_health_val(15 + ((SDL_GetTicks() - startTime) / 1000));
                            p_enemy->set_clips();

                            p_enemy->set_x_pos((rand() % 2) ? 220 : 350);

                            p_enemy->set_y_pos(-150);


                            enemy_lists.push_back(p_enemy);

                        }
                        lastSpawnTime = currentTime;
						// Spawn Lion   

						break;
					case 2:
						// Spawn Dragon and Lion
						
                        if (p_enemy1 != NULL && p_enemy2 != NULL)
                        {
                            p_enemy1->LoadImg("res/Pokemon/Fire + stone dragon/sprite9_idle.png", gRenderer);
                            p_enemy1->set_health_val(15 + ((SDL_GetTicks() - startTime) / 1000));
                            p_enemy1->set_clips();
                            int dragonX = rand() % 2 ? 220 : 350;
                            p_enemy1->set_x_pos(dragonX);
                            p_enemy1->set_y_pos(-150);
                            
							enemy_lists.push_back(p_enemy1);

                            p_enemy2->LoadImg("res/Pokemon/Leaf - lion/sprite3_idle.png", gRenderer);
                            p_enemy2->set_health_val(15 + ((SDL_GetTicks() - startTime) / 1000));
                            p_enemy2->set_clips();
							int lionX = (dragonX == 220) ? 350 : 220; // Ensure lion spawns at a different x position
                            

                            p_enemy2->set_x_pos(lionX);

                            p_enemy2->set_y_pos(-150);


                            enemy_lists.push_back(p_enemy2);
                        }
						lastSpawnTime = currentTime;
						break;
                    }

                    
                }
				

                if (SDL_GetTicks() - startTime - lastChestSpawnTime >= 3000) {
                    Chest* p_chest = new Chest();
                    if (p_chest != NULL)
                    {
                        p_chest->LoadImg("res/Chest-open.png", gRenderer);
                        p_chest->set_clips();
                        p_chest->set_x_pos((rand() % 2) ? 220 : 380);
                        p_chest->set_y_pos(-100);


                        chest_lists.push_back(p_chest);

                    }
                    lastChestSpawnTime = currentTime;
                }

                map.Update(deltaTime, scroll_speed);
                /*spawnManager.Update(deltaTime, scroll_speed);*/
                p_player.Update(deltaTime);
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
				std::cout << enemy_lists.size() << std::endl;
                // Bullet and enemy collide
                for (int i = 0; i < enemy_lists.size(); i++)
                {

                    Enemy* p_enemy = enemy_lists.at(i);
                    if (p_enemy)
                    {
                        eRect.x = p_enemy->GetRect().x;
                        eRect.y = p_enemy->GetRect().y;
                        eRect.w = p_enemy->get_width_frame();
                        eRect.h = p_enemy->get_height_frame();




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
                            std::cout << "Player health: " << p_player.get_health_val() << std::endl;
                            if (p_player.get_health_val() <= 0 && !gameOver)
                            {
                                std::cout << "GAME OVER" << std::endl;
                                gameOver = true;

                            }
                        }
                        else if (!pCol && isColliding)
                        {
                            isColliding = false;
                        }

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

                                bool pCol2 = SDLCommonFunc::CheckCollision(pRect, cRect);
                                //std::cout << "Player and Chest collide" << std::endl;
                                bool cCol = SDLCommonFunc::CheckCollision(cRect, eRect);
                                if (cCol)
                                {
                                    chest_lists.erase(chest_lists.begin() + r);
                                    r--;
                                }
                            }
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

                        bool pCol2 = SDLCommonFunc::CheckCollision(pRect, cRect);
                        //std::cout << "Player and Chest collide" << std::endl;
                        
                      
                            if (pCol2 && !chestCollisionStates[r] && (currentTime - lastDamageTime >= damageCooldown))
                            {
                                chestCollisionStates[r] = true;
                                std::cout << "Chest " << r << " and Player collide" << std::endl;
                                lastDamageTime = currentTime;
                                if (!p_chest->get_is_open()) {

                                    std::cout << "Is Open" << std::endl;
                                    p_chest->Open();
                                    
                                        p_chest->ApplyEffectToPlayer(p_player);
                                        SDL_Color color;


                                        std::string effectText = "";

                                        switch (p_chest->GetType()) {
                                        case CHEST_FIRE_RATE:
                                            effectText = "+ Bullet Speed!";
                                            color = { 0, 255, 255, 255 };
                                            break;
                                        case CHEST_MOVE_SPEED:
                                            effectText = "+ Speed!";
                                            color = { 0, 0, 0, 255 };
                                            break;
                                        case HEALTH_UPGRADE:
                                            effectText = "+ 10 Hp";
                                            color = { 0, 255, 0, 255 };
                                            break;
                                        case BULLET_DAMAGE:
                                            effectText = "+1 Bullet Damage!";
                                            color = { 255, 0, 0, 255 };
                                            break;
                                        }

                                        buffTextList.emplace_back(effectText, p_player.GetRectFrame().x, p_player.GetRectFrame().y, color, chestText);

                                    
                                   


                                }
                            }
                            else if (!pCol2 && chestCollisionStates[r])
                            {
                                chestCollisionStates[r] = false;
                            }
                        


                    }
                }

                for (int i = 0; i < buffTextList.size(); ++i) {
                    buffTextList[i].update(deltaTime);
                    buffTextList[i].render(gRenderer);
                }

                buffTextList.erase(std::remove_if(buffTextList.begin(), buffTextList.end(),
                    [](const BuffText& text) { return text.isExpired(); }), buffTextList.end());

                //Show score
                std::string str_score = "Score: ";
                Uint32 score_val = (SDL_GetTicks() - startTime) / 1000;
                score = score_val;

                std::string str_val = std::to_string(score_val);
                str_score += str_val;

                score_game.setText(str_score);
                score_game.loadFromRenderText(fontScore, gRenderer);
                score_game.RenderText(gRenderer, SCREEN_WIDTH / 2 - 90, 10);

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

              

            }
            else {
				

                SDL_Rect dstRect, bgRect;
                dstRect.w = 400; // chiều rộng ảnh Game Over
                dstRect.h = 200; // chiều cao ảnh Game Over
                dstRect.x = (SCREEN_WIDTH - dstRect.w) / 2;
                dstRect.y = (SCREEN_HEIGHT - dstRect.h) / 2 - 200;

				bgRect.w = SCREEN_WIDTH;
				bgRect.h = SCREEN_HEIGHT;
				bgRect.x = 0;
				bgRect.y = 0;
				SDL_RenderCopy(gRenderer, background, NULL, &bgRect);
                SDL_RenderCopy(gRenderer, gameOverTexture, nullptr, &dstRect);

                std::string str_score = "Your score: ";
				std::string str_val = std::to_string(score);
                str_score += str_val;
                score_game.setText(str_score);
                score_game.loadFromRenderText(fontScoreOver, gRenderer);
                score_game.RenderText(gRenderer, SCREEN_WIDTH / 2 - 190, 300);

				gameOverRender.RenderGameOver(mouseX, mouseY);
            }
            SDL_RenderPresent(gRenderer);
            // Hello
            // Giữ ổn định FPS
            frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < FRAME_DELAY_GAME) {
                SDL_Delay(FRAME_DELAY_GAME - frameTime);
            }

        }
    }
    close();
    return 0;
}