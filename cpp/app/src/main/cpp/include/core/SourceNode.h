/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of SourceNode
 */
#ifndef AVPIPELINE_SOURCE_NODE_H
#define AVPIPELINE_SOURCE_NODE_H

#include <string>
#include "base/MMListener.h"
#include "base/MediaBuffer.h"
#include "ClockCore.h"
#include "base/MediaMeta.h"
#include "base/SimplePool.h"
#include "core/NodeBase.h"

namespace AVPipeline {
struct SourceNode : NodeBase {
    SourceNode(const char *mime, bool isProcThreadCreated, bool isAsync = true)
        : NodeBase(mime, isProcThreadCreated, isAsync)
    {}
    ~SourceNode() override = default;

    virtual RetCode SetUri(const std::string &, const std::map<std::string, std::string> *) = 0;
    virtual RetCode SetUri(int, int64_t, int64_t) = 0;
    virtual MediaParcelSP GetTrackInfo() = 0;
    virtual RetCode GetAllTrackMeta(MediaType, std::vector<MediaMetaSP> &) const = 0;
    virtual RetCode SelectTrack(MediaType, int) = 0;
    virtual int GetSelectedTrack(MediaType) const = 0;
    WriterSP GetWriter(MediaType) override { return nullptr; }
    virtual MediaBufferSP ReadBuffer(MediaType, int64_t)  { return nullptr; }
    virtual RetCode WriteBuffer(const MediaBufferSP &, MediaType) { return ERROR_UNSUPPORTED; };
    virtual std::list<std::string> GetSupportedProtocols() const = 0;
    virtual bool IsSeekable() const = 0;
    virtual RetCode GetDuration(int64_t &durationMs) const = 0;
    virtual bool HasMedia(MediaType) const = 0;
    virtual MediaMetaSP GetMetaData() const = 0;
    MediaMetaSP GetMetaData(MediaType) const override = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(SourceNode);
};
using SourceNodeSP = std::shared_ptr<SourceNode>;
}
#endif // AVPIPELINE_SOURCE_NODE_H
