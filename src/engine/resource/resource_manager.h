#pragma once
#include <memory>
#include <string>
#include <glm/vec2.hpp>

// 前向声明 SDL 类型
struct SDL_Renderer;
struct SDL_Texture;
struct MIX_Audio;
struct TTF_Font;

namespace engine::resource {

// 前向声明内部管理器
class TextureManager;
class AudioManager;
class FontManager;

class ResourceManager {
private:
    // 使用 unique_ptr 确保所有权和自动清理
    std::unique_ptr<TextureManager> texture_manager_;
    std::unique_ptr<AudioManager> audio_manager_;
    std::unique_ptr<FontManager> font_manager_;

public:
    explicit ResourceManager(SDL_Renderer* renderer);

    ~ResourceManager();  // 显式声明析构函数，这是为了能让智能指针正确管理仅有前向声明的类

    void clear();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    // --- 统一资源访问接口 ---
    // -- Texture --
    SDL_Texture* loadTexture(const std::string& file_path);  ///< @brief 载入纹理资源
    SDL_Texture* getTexture(const std::string& file_path);   ///< @brief 尝试获取已加载纹理的指针，如果未加载则尝试加载
    void unloadTexture(const std::string& file_path);        ///< @brief 卸载指定的纹理资源
    glm::vec2 getTextureSize(const std::string& file_path);  ///< @brief 获取指定纹理的尺寸
    void clearTextures();                                    ///< @brief 清空所有纹理资源

    // -- Sound Effects (Chunks) --
    MIX_Audio* loadSound(const std::string& file_path);  ///< @brief 载入音效资源
    MIX_Audio* getSound(const std::string& file_path);   ///< @brief 尝试获取已加载音效的指针，如果未加载则尝试加载
    void unloadSound(const std::string& file_path);      ///< @brief 卸载指定的音效资源
    void clearSounds();                                  ///< @brief 清空所有音效资源

    // -- Music --
    MIX_Audio* loadMusic(const std::string& file_path);  ///< @brief 载入音乐资源
    MIX_Audio* getMusic(const std::string& file_path);   ///< @brief 尝试获取已加载音乐的指针，如果未加载则尝试加载
    void unloadMusic(const std::string& file_path);      ///< @brief 卸载指定的音乐资源
    void clearMusic();                                   ///< @brief 清空所有音乐资源

    // -- Fonts --
    TTF_Font* loadFont(const std::string& file_path, int point_size);  ///< @brief 载入字体资源
    TTF_Font* getFont(const std::string& file_path, int point_size);   ///< @brief 尝试获取已加载字体的指针，如果未加载则尝试加载
    void unloadFont(const std::string& file_path, int point_size);     ///< @brief 卸载指定的字体资源
    void clearFonts();                                                 ///< @brief 清空所有字体资源
};
}  // namespace engine::resource