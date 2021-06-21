/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of clock wrapper
 */
#ifndef _CLOCK_H__
#define _CLOCK_H__

namespace AVPipeline {
struct Clock;
using ClockSP = std::shared_ptr<Clock>;
struct Clock {
    static std::shared_ptr<Clock> Create(uint32_t flag = 0);
    RetCode Pause();
    RetCode Resume();
    RetCode Flush();

    ClockCoreSP ProvideClock();
    RetCode SetClock(const ClockCoreSP &clock);

    void SetAnchorTime(int64_t mediaUs, int64_t realUs, int64_t anchorMaxTime = -1);
    void UpdateMaxAnchorTime(int64_t anchorMaxTime);
    int64_t GetMediaLateUs(int64_t mediaTimeUs);
    RetCode GetCurrentPosition(int64_t &mediaTimeUs);

    enum ClockFlag {
        FLAG_VIDEO_SINK = 1 << 0,
    };

private:
    explicit Clock(uint32_t flag = 0);
    virtual ~Clock() = default;
    RetCode Init();
    static void Destroy(Clock *cache);
    void DeInit() {}

private:
    bool mIsClockOwner { true }; // false means clock provided by other node
    ClockCoreSP mClock { nullptr };
    uint32_t mFlag { 0 };
    bool mIsAudioEos { false };
};
} // end of namespace AVPipeline
#endif // _CLOCK_H__
