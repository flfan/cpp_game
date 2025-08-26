#pragma once
// 资源管理器，负责加载和管理游戏资源，如纹理、音频等
#include <memory>
#include <unordered_map>
#include <string>
#include <SDL3/SDL_render.h>  // 用于 SDL_Texture 和 SDL_Renderer
#include <glm/vec2.hpp>       // 用于 glm::vec2

namespace engine::resource {

class TextureManager final {
    friend class ResourceManager;  // 仅 ResourceManager 可以访问 TextureManager 的私有成员
private:
    struct SDLTextureDeleter {
        void operator()(SDL_Texture* texture) const {
            if (texture != nullptr) {
                SDL_DestroyTexture(texture);
            }
        }
    };

    // 存储文件路径和指向管理纹理的 unique_ptr 的映射。
    std::unordered_map<std::string, std::unique_ptr<SDL_Texture, SDLTextureDeleter>> textures_;

    SDL_Renderer* renderer_ = nullptr;  // 指向主渲染器的非拥有指针
public:
    /**
     * @brief 构造函数，执行初始化。
     * @param renderer 指向有效的 SDL_Renderer 上下文的指针。不能为空。
     * @throws std::runtime_error 如果 renderer 为 nullptr 或初始化失败。
     */
    explicit TextureManager(SDL_Renderer* renderer);

    // 当前设计中，我们只需要一个TextureManager，所有权不变，所以不需要拷贝、移动相关构造及赋值运算符
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    TextureManager(TextureManager&&) = delete;
    TextureManager& operator=(TextureManager&&) = delete;

private:                                                     // 仅供 ResourceManager 访问的方法
    SDL_Texture* loadTexture(const std::string& file_path);  ///< @brief 从文件路径加载纹理
    SDL_Texture* getTexture(const std::string& file_path);   ///< @brief 尝试获取已加载纹理的指针，如果未加载则尝试加载
    glm::vec2 getTextureSize(const std::string& file_path);  ///< @brief 获取指定纹理的尺寸
    void unloadTexture(const std::string& file_path);        ///< @brief 卸载指定的纹理资源
    void clearTextures();                                    ///< @brief 清空所有纹理资源
};
}  // namespace engine::resource