#include "CommonFunc.h"
#include "InfiniteMap.h"
#include "BaseObject.h"

InfiniteScrollingMap::InfiniteScrollingMap(SDL_Renderer* renderer, const std::string& chunk1_path, const std::string& chunk2_path)
    : scroll_y(0) {
    // Load 2 chunk texture
    chunk_textures[0] = IMG_LoadTexture(renderer, chunk1_path.c_str());
    chunk_textures[1] = IMG_LoadTexture(renderer, chunk2_path.c_str());

    if (!chunk_textures[0] || !chunk_textures[1]) {
        std::cerr << "Failed to load map chunks: " << IMG_GetError() << std::endl;
    }

    // Thêm chunk đầu tiên
    active_chunks.push_back({ 0, 0 });
}

InfiniteScrollingMap::~InfiniteScrollingMap()
{

}

void InfiniteScrollingMap::Update(float delta_time, float scroll_speed) {
    scroll_y += scroll_speed * delta_time;

    // Cập nhật vị trí các chunk hiện có
    for (auto& chunk : active_chunks) {
        chunk.second += scroll_speed * delta_time;
    }

    // Xóa chunk đã cuộn qua khỏi màn hình
    if (!active_chunks.empty() && active_chunks[0].second >= SCREEN_HEIGHT) {
        active_chunks.erase(active_chunks.begin());
    }

    // Thêm chunk mới khi chunk cuối bắt đầu đi vào màn hình
    if (active_chunks.empty() ||
        active_chunks.back().second <= SCREEN_HEIGHT) {
        int last_index = active_chunks.empty() ? 0 : active_chunks.back().first;
        int next_index = (last_index + 1) % 2;

        float new_y = active_chunks.empty() ? 0 : active_chunks.back().second - SCREEN_HEIGHT;
        active_chunks.push_back({ next_index, new_y });

      
    }
}

void InfiniteScrollingMap::Render(SDL_Renderer* renderer) {
    // DEBUG: Vẽ nền màu đen trước
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (const auto& chunk : active_chunks) {
        // Chỉ render các chunk đang/ sắp hiển thị
        if (chunk.second > SCREEN_HEIGHT || chunk.second < -SCREEN_HEIGHT) {
            continue;
        }

        SDL_Rect dest_rect = {
            0,
            static_cast<int>(chunk.second),
            SCREEN_WIDTH,
            SCREEN_HEIGHT
        };

        if (SDL_RenderCopy(renderer, chunk_textures[chunk.first], NULL, &dest_rect) < 0) {
            std::cerr << "Render failed: " << SDL_GetError() << std::endl;
        }

     
    }
}