/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of SinkNode
 */
#ifndef AVPIPELINE_SINK_NODE_H
#define AVPIPELINE_SINK_NODE_H

#include <map>
#include <list>
#include <string>
#include "base/MMListener.h"
#include "base/MediaBuffer.h"
#include "ClockCore.h"
#include "base/MediaMeta.h"
#include "base/SimplePool.h"
#include "core/NodeBase.h"
#include "Clock.h"

namespace AVPipeline {
struct SinkNode : NodeBase {
    SinkNode(const char *mime, bool isProcessorThread, bool isAsync) : NodeBase(mime, isProcessorThread, isAsync) {}
    ~SinkNode() override = default;
    RetCode AddDownLink(INode *, MediaType) override;

    // specific methods for sink node
    virtual int64_t GetCurrentPosition() const;
    virtual RetCode SetVolume(double);
    virtual double GetVolume() const;
    virtual RetCode SetMute(bool);
    virtual bool GetMute() const;
    virtual RetCode SetAudioStreamType(int);
    ClockCoreSP ProvideClock() override;
    RetCode SetClock(ClockCoreSP) override;

protected:
    virtual RetCode DoSetVolume(double) { return ERROR_UNSUPPORTED; }
    virtual RetCode DoSetMute(bool) { return ERROR_UNSUPPORTED; }
    virtual RetCode DoSetAudioStreamType(int) { return ERROR_UNSUPPORTED; }
    virtual double DoGetVolume() const { return 0.0; }
    virtual bool DoGetMute() const { return false; }
    virtual int DoGetStreamType() const { return -1; }
    virtual int64_t DoGetCurrentPosition() const { return -1LL; }
    RetCode DoRegisterHandlers() override;

    ClockSP mClock { nullptr };
private:
    DECLARE_HANDLER(OnSetVolume);
    DECLARE_HANDLER(OnGetVolume);
    DECLARE_HANDLER(OnSetMute);
    DECLARE_HANDLER(OnGetMute);
    DECLARE_HANDLER(OnSetStreamType);
    DECLARE_HANDLER(OnGetStreamType);
    DECLARE_HANDLER(OnGetCurrentPosition);
    DISALLOW_COPY_AND_ASSIGN(SinkNode);

};
}
#endif // AVPIPELINE_SINK_NODE_H
