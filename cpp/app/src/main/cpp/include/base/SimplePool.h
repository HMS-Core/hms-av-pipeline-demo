/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: header file of buffer pool
 */
#ifndef SIMPLE_POOL_H
#define SIMPLE_POOL_H

#include <list>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <string>
#include "base/MediaErrors.h"
#include "base/MediaBuffer.h"

namespace AVPipeline {

struct SimplePool;
using SimplePoolSP = std::shared_ptr<SimplePool>;

struct SimplePool {
    explicit SimplePool(const std::string &name) : mName(name) {}
    virtual ~SimplePool() = default;
    void SetBufferDuration(uint64_t timeUs);
    void SetBufferCount(uint32_t count);
    void Reset();
    void WakeUp();
    void Flush();

    RetCode GetBuffer(MediaBufferSP &buffer, int64_t timeOutUs = 0);
    RetCode PutBuffer(const MediaBufferSP &buffer, int64_t timeOutUs = -1);

    std::size_t Size() const;
    uint64_t DurationUs() const;
    bool IsOverRun() const;
    bool IsUnderRun() const;
    bool IsBufferControl() const;

private:

    SimplePool(const SimplePool &copy) = delete;
    SimplePool &operator = (const SimplePool &) = delete;
    static void Destroy(SimplePool *pool);
    void DoWakeUp(bool exit);

    uint64_t DoDurationUs() const;
    bool DoCheckUnderRun() const;
    bool DoCheckOverRun() const;
    RetCode DoPutBuffer(const MediaBufferSP &buffer);
    RetCode DoGetBuffer(MediaBufferSP &buffer);
    void DoFlush();

private:
    uint64_t mHighLevelDurationUs { 0 };
    uint64_t mLowLevelDurationUs { 0 };
    uint32_t mHighLevelBufferCount { 20 };
    uint32_t mLowLevelBufferCount { 10 };

    mutable std::mutex mPoolLock;
    bool mExit { false };
    std::string mName {};
    std::condition_variable mEmptyCondition {};
    std::condition_variable mFullCondition {};
    std::queue<MediaBufferSP> mBufferList {}; // available buffers for producer, the data of the buffer is invalid
    int64_t mLastPts { 0 };
    bool mFlushPending { false };
};
} // namespace AVPipeline

#endif
