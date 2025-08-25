#include "config.h"
#include <fstream>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

namespace engine::core {

Config::Config(const std::string& filepath) {
  loadFromFile(filepath);
}

bool Config::loadFromFile(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    spdlog::warn("配置文件 '{}' 未找到。使用默认设置并创建默认配置文件。", filepath);
    if (!saveToFile(filepath)) {
      spdlog::error("无法创建默认配置文件 '{}'。", filepath);
      return false;
    }
    return false;
  }
  try {
    nlohmann::json config_json;
    file >> config_json;
    fromJson(config_json);
    spdlog::info("成功从 '{}' 加载配置。", filepath);
    return true;
  } catch (const std::exception& e) {
    spdlog::error("读取配置文件 '{}' 时出错：{}。使用默认设置。", filepath, e.what());
  }
  return false;
}

bool Config::saveToFile(const std::string& filepath) {
  std::ofstream file(filepath);
  if (!file.is_open()) {
    spdlog::error("无法打开配置文件 '{}' 进行写入。", filepath);
    return false;
  }
  
  try {
    nlohmann::ordered_json json = toJson();
    file << json.dump(4);
    spdlog::info("成功保存配置到 '{}'。", filepath);
    return true;
  } catch (const std::exception& e) {
    spdlog::error("写入配置文件 '{}' 时出错：{}", filepath, e.what());
  }
  return false;
}

void Config::fromJson(const nlohmann::json& config_json) {
  if (config_json.contains("window")) {
    const auto& window_config = config_json["window"];
    window_title_ = window_config.value("title", window_title_);
    window_width_ = window_config.value("width", window_width_);
    window_height_ = window_config.value("height", window_height_);
    window_resizable_ = window_config.value("resizable", window_resizable_);
  }
  if (config_json.contains("graphics")) {
      const auto& graphics_config = config_json["graphics"];
      vsync_enabled_ = graphics_config.value("vsync", vsync_enabled_);
  }
  if (config_json.contains("performance")) {
      const auto& perf_config = config_json["performance"];
      target_fps_ = perf_config.value("target_fps", target_fps_);
      if (target_fps_ < 0) {
          spdlog::warn("目标 FPS 不能为负数。设置为 0（无限制）。");
          target_fps_ = 0;
      }
  }
  if (config_json.contains("audio")) {
      const auto& audio_config = config_json["audio"];
      music_volume_ = audio_config.value("music_volume", music_volume_);
      sound_volume_ = audio_config.value("sound_volume", sound_volume_);
  }

  // 从 JSON 加载 input_mappings
  if (config_json.contains("input_mappings") && config_json["input_mappings"].is_object()) {
      const auto& mappings_json = config_json["input_mappings"];
      try {
          // 直接尝试从 JSON 对象转换为 map<string, vector<string>>
          auto input_mappings = mappings_json.get<std::unordered_map<std::string, std::vector<std::string>>>();
          // 如果成功，则将 input_mappings 移动到 input_mappings_
          input_mappings_ = std::move(input_mappings);
          spdlog::trace("成功从配置加载输入映射。");
      } catch (const std::exception& e) {
          spdlog::warn("配置加载警告：解析 'input_mappings' 时发生异常。使用默认映射。错误：{}", e.what());
      }
  } else {
      spdlog::trace("配置跟踪：未找到 'input_mappings' 部分或不是对象。使用头文件中定义的默认映射。");
  }
}

nlohmann::ordered_json Config::toJson() const {
  return nlohmann::ordered_json{
      {"window", {
          {"title", window_title_},
          {"width", window_width_},
          {"height", window_height_},
          {"resizable", window_resizable_}
      }},
      {"graphics", {
          {"vsync", vsync_enabled_}
      }},
      {"performance", {
          {"target_fps", target_fps_}
      }},
      {"audio", {
          {"music_volume", music_volume_},
          {"sound_volume", sound_volume_}
      }},
      {"input_mappings", input_mappings_}
  };
}

}  // namespace engine::core