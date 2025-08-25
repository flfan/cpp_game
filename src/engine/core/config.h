#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json_fwd.hpp>

namespace engine::core {

class Config final {
public:
    // --- 默认配置值 --- (为了方便拓展，全部设置为公有)
    // 窗口设置
    std::string window_title_ = "SunnyLand";
    int window_width_ = 1280;
    int window_height_ = 720;
    bool window_resizable_ = true;

    // 图形设置
    bool vsync_enabled_ = true;  ///< @brief 是否启用垂直同步

    // 性能设置
    int target_fps_ = 144;  ///< @brief 目标 FPS 设置，0 表示不限制

    // 音频设置
    float music_volume_ = 0.5F;
    float sound_volume_ = 0.5F;

    // 存储动作名称到 SDL Scancode 名称列表的映射
    std::unordered_map<std::string, std::vector<std::string>> input_mappings_ = {
        // 提供一些合理的默认值，以防配置文件加载失败或缺少此部分
        {"move_left", {"A", "Left"}},
        {"move_right", {"D", "Right"}},
        {"move_up", {"W", "Up"}},
        {"move_down", {"S", "Down"}},
        {"jump", {"J", "Space"}},
        {"attack", {"K", "MouseLeft"}},
        {"pause", {"P", "Escape"}},
        // 可以继续添加更多默认动作
    };

    explicit Config(const std::string& filepath);  ///< @brief 构造函数，指定配置文件路径。

    // 删除拷贝和移动语义
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(Config&&) = delete;

    bool loadFromFile(const std::string& filepath);              ///< @brief 从指定的 JSON 文件加载配置。成功返回 true，否则返回 false。
    [[nodiscard]] bool saveToFile(const std::string& filepath);  ///< @brief 将当前配置保存到指定的 JSON 文件。成功返回 true，否则返回 false。

private:
    void fromJson(const nlohmann::json& config_json);     ///< @brief 从 JSON 对象反序列化配置。
    [[nodiscard]] nlohmann::ordered_json toJson() const;  ///< @brief 将当前配置转换为 JSON 对象（按顺序）。
};

}  // namespace engine::core