#include "audio_manager.h"
#include <spdlog/spdlog.h>
#include <stdexcept>

namespace engine::resource {

// 构造函数：初始化SDL_mixer
AudioManager::AudioManager() {
    // 使用所需的格式初始化SDL_mixer（推荐OGG、MP3）
    if (!MIX_Init()) {
        throw std::runtime_error("AudioManager 错误: Mix_Init 失败: " + std::string(SDL_GetError()));
    }

    // SDL3打开音频设备的方法。默认值：44100 Hz，默认格式，2声道（立体声），2048采样块大小
    mixer_ = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);  // 获取当前打开的Mix_Mixer指针

    if (mixer_ == nullptr) {
        MIX_Quit();  // 如果OpenAudio失败，先清理Mix_Init，再抛出异常
        throw std::runtime_error("AudioManager 错误: Mix_OpenAudio 失败: " + std::string(SDL_GetError()));
    }
    track_ = MIX_CreateTrack(mixer_);
    spdlog::trace("AudioManager 构造成功。");
}

AudioManager::~AudioManager() {
    // 立即停止所有音频播放
    MIX_StopTrack(track_, 0);  // 停止所有音效

    // 清理资源映射（unique_ptrs会调用删除器）
    clearSounds();
    clearMusic();

    // 关闭音频设备
    MIX_DestroyMixer(mixer_);

    // 退出SDL_mixer子系统
    MIX_Quit();
    spdlog::trace("AudioManager 析构成功。");
}

// --- 音效管理 ---
MIX_Audio* AudioManager::loadSound(const std::string& file_path) {
    // 首先检查缓存
    auto it = sounds_.find(file_path);
    if (it != sounds_.end()) {
        return it->second.get();
    }

    // 加载音效块
    spdlog::debug("加载音效: {}", file_path);
    MIX_Audio* raw_chunk = MIX_LoadAudio(mixer_, file_path.c_str(), false);
    if (!raw_chunk) {
        spdlog::error("加载音效失败: '{}': {}", file_path, SDL_GetError());
        return nullptr;
    }

    // 使用unique_ptr存储在缓存中
    sounds_.emplace(file_path, std::unique_ptr<MIX_Audio, SDLMixAudioDeleter>(raw_chunk));
    spdlog::debug("成功加载并缓存音效: {}", file_path);
    return raw_chunk;
}

MIX_Audio* AudioManager::getSound(const std::string& file_path) {
    auto it = sounds_.find(file_path);
    if (it != sounds_.end()) {
        return it->second.get();
    }
    spdlog::warn("音效 '{}' 未找到缓存，尝试加载。", file_path);
    return loadSound(file_path);
}

void AudioManager::unloadSound(const std::string& file_path) {
    auto it = sounds_.find(file_path);
    if (it != sounds_.end()) {
        spdlog::debug("卸载音效: {}", file_path);
        sounds_.erase(it);  // unique_ptr处理Mix_FreeChunk
    } else {
        spdlog::warn("尝试卸载不存在的音效: {}", file_path);
    }
}

void AudioManager::clearSounds() {
    if (!sounds_.empty()) {
        spdlog::debug("正在清除所有 {} 个缓存的音效。", sounds_.size());
        sounds_.clear();  // unique_ptr处理删除
    }
}

// --- 音乐管理 ---
MIX_Audio* AudioManager::loadMusic(const std::string& file_path) {
    // 首先检查缓存
    auto it = musics_.find(file_path);
    if (it != musics_.end()) {
        return it->second.get();
    }

    // 加载音乐
    spdlog::debug("加载音乐: {}", file_path);
    MIX_Audio* raw_music = MIX_LoadAudio(mixer_, file_path.c_str(), false);
    if (!raw_music) {
        spdlog::error("加载音乐失败: '{}': {}", file_path, SDL_GetError());
        return nullptr;
    }

    // 使用unique_ptr存储在缓存中
    musics_.emplace(file_path, std::unique_ptr<MIX_Audio, SDLMixAudioDeleter>(raw_music));
    spdlog::debug("成功加载并缓存音乐: {}", file_path);
    return raw_music;
}

MIX_Audio* AudioManager::getMusic(const std::string& file_path) {
    auto it = musics_.find(file_path);
    if (it != musics_.end()) {
        return it->second.get();
    }
    spdlog::warn("音乐 '{}' 未找到缓存，尝试加载。", file_path);
    return loadMusic(file_path);
}

void AudioManager::unloadMusic(const std::string& file_path) {
    auto it = musics_.find(file_path);
    if (it != musics_.end()) {
        spdlog::debug("卸载音乐: {}", file_path);
        musics_.erase(it);  // unique_ptr处理Mix_FreeMusic
    } else {
        spdlog::warn("尝试卸载不存在的音乐: {}", file_path);
    }
}

void AudioManager::clearMusic() {
    if (!musics_.empty()) {
        spdlog::debug("正在清除所有 {} 个缓存的音乐曲目。", musics_.size());
        musics_.clear();  // unique_ptr处理删除
    }
}

void AudioManager::clearAudio() {
    clearSounds();
    clearMusic();
}

}  // namespace engine::resource
