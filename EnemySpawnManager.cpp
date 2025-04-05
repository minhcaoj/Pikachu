//#include "EnemySpawnManager.h"
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include "Enemy.h"
//
//EnemySpawnManager::EnemySpawnManager() :
//    spawnTimer(0),
//    spawnInterval(2.0f),  // 2 giây spawn 1 quái
//    renderer(nullptr),
//    enemyTexture(nullptr),
//    width_frame(0),
//    height_frame(0)
//{
//    // Khởi tạo random seed
//    std::srand(std::time(nullptr));
//}
//
//bool EnemySpawnManager::LoadEnemyTexture(std::string path, SDL_Renderer* render, float scaleFactor) {
//   
//    bool ret = BaseObject::LoadImg(path, render, 1);
//    if (ret == true)
//    {
//        width_frame = 96;
//        height_frame = 96;
//    }
//    return ret;
//}
//
//
//void EnemySpawnManager::Update(float deltaTime, float scrollSpeed) {
//    // Debug spawn timer
//    static int updateCount = 0;
//    if (updateCount++ % 60 == 0) {
//        std::cout << "Spawn timer: " << spawnTimer << "/" << spawnInterval << std::endl;
//    }
//
//    spawnTimer += deltaTime;
//
//    if (spawnTimer >= spawnInterval) {
//        spawnTimer = 0;
//
//        // Chọn vị trí spawn (250 hoặc 350)
//        int spawnX = (std::rand() % 2) ? 250 : 350;
//
//        Enemy newEnemy;
//        if (enemyTexture) {
//            // Phương thức mới đảm bảo khởi tạo đúng
//            if (newEnemy.Initialize(enemyTexture, renderer)) {
//                newEnemy.SetPosition(spawnX, -50);
//                enemies.push_back(newEnemy);
//                std::cout << "Spawned NEW enemy at (" << spawnX << ", -50)" << std::endl;
//            }
//        }
//    }
//
//    // Cập nhật và xóa enemy
//    for (auto it = enemies.begin(); it != enemies.end(); ) {
//        it->Update(scrollSpeed, deltaTime);
//
//        if (!it->IsActive()) {
//            std::cout << "Removing inactive enemy" << std::endl;
//            it = enemies.erase(it);
//        }
//        else {
//            ++it;
//        }
//    }
//}
//
//void EnemySpawnManager::Render() {
//    for (auto& enemy : enemies) {
//        enemy.Render(renderer);
//    }
//}
//
//void EnemySpawnManager::SetRenderer(SDL_Renderer* renderer) {
//    this->renderer = renderer;
//    std::cout << "Renderer set for EnemySpawnManager" << std::endl;
//}
//
//std::vector<Enemy>& EnemySpawnManager::GetEnemies() {
//    return enemies;
//}
//
//void EnemySpawnManager::CleanUp() {
//    if (enemyTexture) {
//        SDL_DestroyTexture(enemyTexture);
//        enemyTexture = nullptr;
//    }
//    enemies.clear();
//}