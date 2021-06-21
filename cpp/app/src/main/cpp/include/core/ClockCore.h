/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of clock
 */
#ifndef __CLOCK_CORE_H__
#define __CLOCK_CORE_H__

#include <ctime>
#include <memory>
#include <mutex>
#include "base/BaseMacros.h"
#include "base/MediaErrors.h"

namespace AVPipeline {
struct ClockCore;
using ClockCoreSP = std::shared_ptr<ClockCore>;
struct ClockCore {
    ClockCore() = default;
    virtual ~ClockCore() = default;
    static int64_t GetNowUs();

private:
    friend struct Clock;
    virtual RetCode Pause();
    virtual RetCode Resume();
    virtual RetCode Flush();

    int64_t GetAnchorTimeMediaUs() const;
    int64_t GetMediaLateUs(int64_t mediaTimeUs) const;
    void SetAnchorTime(int64_t mediaUs, int64_t realUs, int64_t anchorMaxTime = -1);
    RetCode GetCurrentPosition(int64_t &mediaUs) const;
    void UpdateMaxAnchorTime(int64_t anchorMaxTime);

    // lock by caller
    RetCode DoGetCurrentPosition(int64_t &mediaUs) const;
    RetCode DoGetCurrentPositionFromAnchor(int64_t &mediaUs) const;
    void DoSetAnchorTime(int64_t mediaUs, int64_t realUs, int64_t anchorMaxTime = -1);
    RetCode DoFlush();

private:
    int64_t mAnchorTimeMediaUs { -1LL };
    int64_t mAnchorTimeRealUs { -1LL };
    int64_t mAnchorTimeMaxUs { -1LL };
    int64_t mPauseStartedTimeRealUs { -1LL };
    bool mPaused { false };
    int64_t mPausePositionMediaTimeUs { -1LL };
    mutable std::mutex mLock {};

private:
    DISALLOW_COPY_AND_ASSIGN(ClockCore);
};
}

#endif // __CLOCK_CORE_H__
