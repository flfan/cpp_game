#pragma once
#include <memory>

// 前向声明, 减少头文件的依赖，增加编译速度
struct SDL_Window;
struct SDL_Renderer;

namespace engine::core {
class Config;

class GameApp final {
private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* sdl_renderer_ = nullptr;
    bool is_running_ = false;

    std::unique_ptr<Config> config_;

public:
    GameApp();
    ~GameApp();

    // 禁用拷贝构造和赋值 解释为什么禁用
    GameApp(const GameApp&) = delete;
    GameApp& operator=(const GameApp&) = delete;
    GameApp(GameApp&&) = delete;
    GameApp& operator=(GameApp&&) = delete;

    // 禁用默认构造函数

    /**
     * @brief 运行游戏应用程序，其中会调用init()，然后进入主循环，离开循环后自动调用close()。
     */
    void run();

private:
    [[nodiscard]] bool init();  // nodiscard 表示该函数返回值不应该被忽略
    void handleEvents();
    void update(float delta_time);
    void render();
    void close();

    [[nodiscard]] bool initSDL();
    [[nodiscard]] bool initConfig();
};
}  // namespace engine::core