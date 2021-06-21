/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of MMListener
 */
#ifndef MM_LISTENER_H
#define MM_LISTENER_H
#include <memory>
#include "base/MediaParcel.h"
#include "base/MediaErrors.h"
#include "base/MediaBuffer.h"
#include "core/NodeUtils.h"

namespace AVPipeline {
struct MMListener {
    MMListener() = default;
    virtual ~MMListener() = default;
    virtual void OnMessage(int, int, int, MediaParcelSP) { }
    virtual void OnBuffer(MediaBufferSP, MediaType) { }

private:
    DISALLOW_COPY_AND_ASSIGN(MMListener);
};
}

#endif // MM_LISTENER_H
