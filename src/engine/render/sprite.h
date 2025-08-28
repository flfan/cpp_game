#pragma once

#include <string>
#include <optional>
#include <SDL3/SDL_rect.h>  // 用于 SDL_FRect

namespace engine::render {
class Sprite final {
private:
    std::string texture_id_;                ///< @brief 纹理资源的标识符
    std::optional<SDL_FRect> source_rect_;  ///< @brief 可选：要绘制的纹理部分
    bool is_flipped_ = false;               ///< @brief 是否水平翻转

public:
    /**
     * @brief 构造一个精灵
     *
     * @param texture_id 纹理资源的标识符。不应为空。
     * @param source_rect 可选的源矩形（SDL_FRect），定义要使用的纹理部分。如果为 std::nullopt，则使用整个纹理。
     * @param is_flipped 是否水平翻转
     */
    explicit Sprite(const std::string& texture_id, const std::optional<SDL_FRect>& source_rect = std::nullopt, bool is_flipped = false)
        : texture_id_(texture_id),
          source_rect_(source_rect),
          is_flipped_(is_flipped) {}

    // --- getters and setters ---
    [[nodiscard]] const std::string& getTextureId() const { return texture_id_; }                 ///< @brief 获取纹理 ID
    [[nodiscard]] const std::optional<SDL_FRect>& getSourceRect() const { return source_rect_; }  ///< @brief 获取源矩形 (如果使用整个纹理则为 std::nullopt)
    [[nodiscard]] bool isFlipped() const { return is_flipped_; }                                  ///< @brief 获取是否水平翻转

    void setTextureId(const std::string& texture_id) { texture_id_ = texture_id; }                   ///< @brief 设置纹理 ID
    void setSourceRect(const std::optional<SDL_FRect>& source_rect) { source_rect_ = source_rect; }  ///< @brief 设置源矩形 (如果使用整个纹理则为 std::nullopt)
    void setFlipped(bool flipped) { is_flipped_ = flipped; }
};
}  // namespace engine::render