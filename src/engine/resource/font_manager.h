#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <SDL3_ttf/SDL_ttf.h>
#include <utility>     // 用于 std::pair
#include <functional>  // 用于 std::hash

namespace engine::resource {

using FontKey = std::pair<std::string, int>;  // 字体文件路径 + 字体大小

struct FontKeyHash {
    std::size_t operator()(const FontKey& key) const {
        std::hash<std::string> string_hasher;
        std::hash<int> int_hasher;
        return string_hasher(key.first) ^ int_hasher(key.second);  // 异或运算符 ^ 按位计算，每一位的两个值不同为1，相同为0，这是合并两个哈希值的简单方法
    }
};

class FontManager final {
    friend class ResourceManager;

private:
    struct SDLFontDeleter {
        void operator()(TTF_Font* font) const {
            if (font != nullptr) {
                TTF_CloseFont(font);
            }
        }
    };
    std::unordered_map<FontKey, std::unique_ptr<TTF_Font, SDLFontDeleter>, FontKeyHash> fonts_;

public:
    /**
     * @brief 构造函数。初始化 SDL_ttf。
     * @throws std::runtime_error 如果 SDL_ttf 初始化失败。
     */
    FontManager();

    ~FontManager();  ///< @brief 需要手动添加析构函数，清理资源并关闭 SDL_ttf。

    // 当前设计中，我们只需要一个FontManager，所有权不变，所以不需要拷贝、移动相关构造及赋值运算符
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;
    FontManager(FontManager&&) = delete;
    FontManager& operator=(FontManager&&) = delete;

private:                                                               // 仅由 ResourceManager（和内部）访问的方法
    TTF_Font* loadFont(const std::string& file_path, int point_size);  ///< @brief 从文件路径加载指定点大小的字体
    TTF_Font* getFont(const std::string& file_path, int point_size);   ///< @brief 尝试获取已加载字体的指针，如果未加载则尝试加载
    void unloadFont(const std::string& file_path, int point_size);     ///< @brief 卸载特定字体（通过路径和大小标识）
    void clearFonts();                                                 ///< @brief 清空所有缓存的字体
};
}  // namespace engine::resource