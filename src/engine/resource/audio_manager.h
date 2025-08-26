#pragma once
// 资源管理器，负责加载和管理游戏资源，如纹理、音频等
#include <memory>
#include <unordered_map>
#include <string>
#include <SDL3_mixer/SDL_mixer.h>

namespace engine::resource {
class AudioManager final {
    friend class ResourceManager;  // 仅 ResourceManager 可以访问 AudioManager 的私有成员

private:
    struct SDLMixAudioDeleter {
        void operator()(MIX_Audio* chunk) {
            if (chunk != nullptr) {
                MIX_DestroyAudio(chunk);
            }
        };
    };

    std::unordered_map<std::string, std::unique_ptr<MIX_Audio, SDLMixAudioDeleter>> sounds_;
    std::unordered_map<std::string, std::unique_ptr<MIX_Audio, SDLMixAudioDeleter>> musics_;
    MIX_Mixer* mixer_ = nullptr;  // 指向Mix_Mixer的非拥有指针
    MIX_Track* track_ = nullptr;  // 指向Mix_Track的非拥有指针

public:
    /**
     * @brief 构造函数。初始化 SDL_mixer 并打开音频设备。
     * @throws std::runtime_error 如果 SDL_mixer 初始化或打开音频设备失败。
     */
    AudioManager();

    ~AudioManager();  ///< @brief 需要手动添加析构函数，清理资源并关闭 SDL_mixer。

    // 当前设计中，我们只需要一个AudioManager，所有权不变，所以不需要拷贝、移动相关构造及赋值运算符
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    AudioManager(AudioManager&&) = delete;
    AudioManager& operator=(AudioManager&&) = delete;

private:                                                 // 仅供 ResourceManager 访问的方法
    MIX_Audio* loadSound(const std::string& file_path);  ///< @brief 从文件路径加载音效
    MIX_Audio* getSound(const std::string& file_path);   ///< @brief 尝试获取已加载音效的指针，如果未加载则尝试加载
    void unloadSound(const std::string& file_path);      ///< @brief 卸载指定的音效资源
    void clearSounds();                                  ///< @brief 清空所有音效资源

    MIX_Audio* loadMusic(const std::string& file_path);  ///< @brief 从文件路径加载音乐
    MIX_Audio* getMusic(const std::string& file_path);   ///< @brief 尝试获取已加载音乐的指针，如果未加载则尝试加载
    void unloadMusic(const std::string& file_path);      ///< @brief 卸载指定的音乐资源
    void clearMusic();                                   ///< @brief 清空所有音乐资源

    void clearAudio();  ///< @brief 清空所有音频资源
};
}  // namespace engine::resource