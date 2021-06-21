/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of media filter
 */
#ifndef MEDIA_FILTER_H
#define MEDIA_FILTER_H
#include <memory>
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include "base/MMListener.h"
#include "base/MediaMeta.h"
#include "base/MediaBuffer.h"
#include "base/MediaErrors.h"

namespace AVPipeline {
struct MediaFilter final {
    static std::shared_ptr<MediaFilter> Create(const MediaMetaSP &meta);
    RetCode SetListener(const std::weak_ptr<MMListener>& listener);
    RetCode Start();
    RetCode Stop();
    RetCode SetParameter(const MediaMetaSP &meta);
    RetCode GetParameter(MediaMetaSP &meta) const;
    RetCode WriteBuffer(const MediaBufferSP &buffer, MediaType type);

private:
    MediaFilter() = default;
    ~MediaFilter() = default;

private:
    RetCode Prepare();
    void Reset();
    RetCode Init();
    void DeInit();
    static void Destroy(MediaFilter *filter);

private:
    struct MediaFilterImpl;
    std::shared_ptr<MediaFilterImpl> mImpl { nullptr };
    mutable std::mutex mLock;

private:
    DISALLOW_COPY_AND_ASSIGN(MediaFilter);
};
} // namespace AVPipeline

#endif /* MEDIA_FILTER_H */
