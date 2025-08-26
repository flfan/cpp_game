#pragma once
#include <SDL3/SDL_stdinc.h>

namespace engine::core {

class Time final {
private:
    Uint64 last_time_ = 0.0;
    Uint64 frame_start_time_ = 0.0;
    double delta_time_ = 0.0;
    double time_scale_ = 1.0;
    // 目标帧率限制，0表示不限制
    int target_fps_ = 0;
    double target_frame_time_ = 0.0;

public:
    Time();

    // delete copy constructor and assignment operator
    Time(const Time&) = delete;
    Time& operator=(const Time&) = delete;
    Time(Time&&) = delete;
    Time& operator=(Time&&) = delete;

    /**
     * @brief 每帧开始时调用，更新内部时间状态并计算 DeltaTime。
     */
    void update();

    /**
     * @brief 获取经过时间缩放调整后的帧间时间差 (DeltaTime)。
     *
     * @return double 缩放后的 DeltaTime (秒)。
     */
    float getDeltaTime() const;

    /**
     * @brief 获取未经过时间缩放的原始帧间时间差。
     *
     * @return double 未缩放的 DeltaTime (秒)。
     */
    float getUnscaledDeltaTime() const;

    /**
     * @brief 设置时间缩放因子。
     *
     * @param scale 时间缩放值。1.0 为正常速度，< 1.0 为慢动作，> 1.0 为快进。
     *              不允许负值。
     */
    void setTimeScale(float scale);

    /**
     * @brief 获取当前的时间缩放因子。
     *
     * @return float 当前的时间缩放因子。
     */
    float getTimeScale() const;

    /**
     * @brief 设置目标帧率。
     *
     * @param fps 目标每秒帧数。设置为 0 表示不限制帧率。负值将被视为 0。
     */
    void setTargetFps(int fps);

    /**
     * @brief 获取当前设置的目标帧率。
     *
     * @return int 目标 FPS，0 表示不限制。
     */
    int getTargetFps() const;

private:
    void limitFrameRate(double current_delta_time);
};

}  // namespace engine::core