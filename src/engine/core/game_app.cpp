#include "game_app.h"
#include <spdlog/spdlog.h>
#include <SDL3/SDL.h>
#include "config.h"

namespace engine::core {

GameApp::GameApp() = default;
GameApp::~GameApp() {
    if (is_running_) {
        spdlog::warn("GameApp 被销毁时没有显式关闭。现在关闭。 ...");
        close();
    }
};

void GameApp::run() {
    if (!init()) {
        spdlog::error("初始化失败，无法运行游戏。");
        return;
    }
    // while (is_running_) {
    // handleEvents();
    // update(delta_time);
    // render();
    // }
    // close();
}

bool GameApp::init() {
    spdlog::set_level(spdlog::level::trace);
    spdlog::trace("初始化 GameApp ...");
    if (!initConfig()) {
        spdlog::error("初始化配置失败。");
        return false;
    }
    if (!initSDL()) {
        spdlog::error("初始化 SDL 失败。");
        return false;
    }
    is_running_ = true;
    spdlog::info("初始化 GameApp 成功。");
    return true;
}

bool GameApp::initSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        spdlog::error("SDL 初始化失败! SDL错误: {}", SDL_GetError());
        return false;
    }

    window_ = SDL_CreateWindow("Game", 800, 600, SDL_WINDOW_RESIZABLE);
    if (window_ == nullptr) {
        spdlog::error("窗口创建失败! SDL错误: {}", SDL_GetError());
        return false;
    }

    sdl_renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (sdl_renderer_ == nullptr) {
        spdlog::error("渲染器创建失败! SDL错误: {}", SDL_GetError());
        return false;
    }

    spdlog::trace("SDL 初始化成功。");
    return true;
}

bool GameApp::initConfig() {
    try {
        config_ = std::make_unique<engine::core::Config>("assets/config.json");
    } catch (const std::exception& e) {
        spdlog::error("初始化配置失败: {}", e.what());
        return false;
    }
    spdlog::trace("配置初始化成功。");
    return true;
}

void GameApp::close() {
    spdlog::trace("关闭 GameApp ...");

    if (sdl_renderer_ != nullptr) {
        SDL_DestroyRenderer(sdl_renderer_);
        sdl_renderer_ = nullptr;
    }
    if (window_ != nullptr) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    SDL_Quit();
    is_running_ = false;
}

}  // namespace engine::core