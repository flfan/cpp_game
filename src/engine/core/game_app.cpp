#include "game_app.h"
#include <spdlog/spdlog.h>
#include <SDL3/SDL.h>
#include "config.h"
#include "time.h"
#include "../input/input_manager.h"

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
    while (is_running_) {
        time_->update();
        auto delta_time = time_->getDeltaTime();
        input_manager_->update();  // 每帧首先更新输入管理器

        handleEvents();
        update(delta_time);
        render();
    }
    close();
}

void GameApp::update(float /* delta_time */) {
    // 游戏逻辑更新
    // testCamera();
}

void GameApp::handleEvents() {
    if (input_manager_->shouldQuit()) {
        spdlog::trace("GameApp 收到来自 InputManager 的退出请求。");
        is_running_ = false;
        return;
    }

    testInputManager();
}

void GameApp::render() {
    // 清除屏幕
    SDL_SetRenderDrawColor(sdl_renderer_, 0, 0, 0, 255);
    SDL_RenderClear(sdl_renderer_);

    // 这里可以添加渲染代码

    // 更新屏幕
    SDL_RenderPresent(sdl_renderer_);
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
    if (!initTime()) {
        spdlog::error("初始化时间管理失败。");
        return false;
    }
    if (!initInputManager()) {
        spdlog::error("初始化输入管理器失败。");
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

    window_ = SDL_CreateWindow(config_->window_title_.c_str(), config_->window_width_, config_->window_height_, SDL_WINDOW_RESIZABLE);
    if (window_ == nullptr) {
        spdlog::error("无法创建窗口! SDL错误: {}", SDL_GetError());
        return false;
    }

    sdl_renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (sdl_renderer_ == nullptr) {
        spdlog::error("无法创建渲染器! SDL错误: {}", SDL_GetError());
        return false;
    }

    // 设置 VSync (注意: VSync 开启时，驱动程序会尝试将帧率限制到显示器刷新率，有可能会覆盖我们手动设置的 target_fps)
    int vsync_mode = config_->vsync_enabled_ ? SDL_RENDERER_VSYNC_ADAPTIVE : SDL_RENDERER_VSYNC_DISABLED;
    SDL_SetRenderVSync(sdl_renderer_, vsync_mode);
    spdlog::trace("VSync 设置为: {}", config_->vsync_enabled_ ? "Enabled" : "Disabled");

    // 设置逻辑分辨率为窗口大小的一半（针对像素游戏）
    SDL_SetRenderLogicalPresentation(sdl_renderer_, config_->window_width_ / 2, config_->window_height_ / 2, SDL_LOGICAL_PRESENTATION_LETTERBOX);
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

bool GameApp::initTime() {
    try {
        time_ = std::make_unique<Time>();
    } catch (const std::exception& e) {
        spdlog::error("初始化时间管理失败: {}", e.what());
        return false;
    }
    time_->setTargetFps(config_->target_fps_);
    spdlog::trace("时间管理初始化成功。");
    return true;
}

bool GameApp::initInputManager() {
    try {
        input_manager_ = std::make_unique<engine::input::InputManager>(sdl_renderer_, config_.get());
    } catch (const std::exception& e) {
        spdlog::error("初始化输入管理器失败: {}", e.what());
        return false;
    }
    spdlog::trace("输入管理器初始化成功。");
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

void GameApp::testInputManager() {
    std::vector<std::string> actions = {
        "move_up",
        "move_down",
        "move_left",
        "move_right",
        "jump",
        "attack",
        "pause",
        "MouseLeftClick",
        "MouseRightClick"};

    for (const auto& action : actions) {
        if (input_manager_->isActionPressed(action)) {
            spdlog::info(" {} 按下 ", action);
        }
        if (input_manager_->isActionReleased(action)) {
            spdlog::info(" {} 抬起 ", action);
        }
        if (input_manager_->isActionDown(action)) {
            spdlog::info(" {} 按下中 ", action);
        }
    }
}

}  // namespace engine::core