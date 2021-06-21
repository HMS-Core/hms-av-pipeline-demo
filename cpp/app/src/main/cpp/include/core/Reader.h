/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of Reader
 */
#ifndef READER_H
#define READER_H
#include "base/MediaBuffer.h"
#include "base/MediaMeta.h"
#include "base/SimplePool.h"

namespace AVPipeline {
struct INode;
struct Reader {
    Reader(INode &node, MediaType type) : mNode(node), mType(type) {}
    virtual ~Reader() = default;
    virtual RetCode Read(MediaBufferSP &buffer);
    virtual MediaMetaSP GetMetaData() const;

protected:
    INode &mNode;
    MediaType mType { MediaType::MT_MAX };
};
} // namespace AVPipeline

#endif // READER_H
