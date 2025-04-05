#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
class InfiniteScrollingMap : public BaseObject{
private:
    SDL_Texture* chunk_textures[2];  // Lưu 2 texture chunk
    float scroll_y;                  // Vị trí cuộn hiện tại
    std::vector<std::pair<int, float>> active_chunks; 

public:
    InfiniteScrollingMap(SDL_Renderer* renderer, const std::string& chunk1_path, const std::string& chunk2_path);
    ~InfiniteScrollingMap();

    void Update(float delta_time, float scroll_speed);
    void Render(SDL_Renderer* render);

    
};