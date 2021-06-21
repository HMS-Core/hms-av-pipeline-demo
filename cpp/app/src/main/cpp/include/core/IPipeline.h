/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of IPipeline
 */
#ifndef AVPIPELINE_IPIPELINE_H
#define AVPIPELINE_IPIPELINE_H

#include <vector>
#include "INode.h"

namespace AVPipeline {
struct IPipeline;
using PipelineSP = std::shared_ptr<IPipeline>;
struct IPipeline {
    struct PipelineListener {
        PipelineListener() = default;
        virtual ~PipelineListener() = default;
        virtual void OnMessage(int, int, int, MediaParcelSP) { }
        virtual void OnBuffer(int, MediaBufferSP, MediaType) { }

    private:
        DISALLOW_COPY_AND_ASSIGN(PipelineListener);
    };
    virtual RetCode Init() = 0;
    virtual void DeInit() = 0;
    virtual RetCode Prepare(bool isAsync = true) = 0;
    virtual RetCode Start() = 0;
    virtual RetCode Stop() = 0;
    virtual RetCode Pause() = 0;
    virtual RetCode Resume() = 0;
    virtual RetCode Reset() = 0;
    virtual RetCode Flush() = 0;
    virtual RetCode GetState(INode::State &state) const = 0;
    virtual RetCode SetParameter(const MediaMetaSP &) = 0;
    virtual RetCode GetParameter(MediaMetaSP &) const = 0;
    virtual RetCode WriteBuffer(const MediaBufferSP &buffer, MediaType type) = 0;
    virtual void SetListener(std::weak_ptr<PipelineListener> listener) = 0;

protected:
    virtual std::vector<NodeSP> GetSourceNode() const = 0;
    virtual std::vector<NodeSP> GetSinkNode(MediaType type) const = 0;
    virtual size_t GetSinkNodeSize() const = 0;
    virtual const char *Name() = 0;
}; // IPipeline
} // namespace AVPipeline

#endif // AVPIPELINE_IPIPELINE_H
