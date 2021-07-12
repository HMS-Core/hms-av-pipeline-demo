/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of INode
 */
#ifndef INODE_H
#define INODE_H

#include <map>
#include <list>
#include <string>
#include <functional>
#include "base/MMListener.h"
#include "base/MediaBuffer.h"
#include "ClockCore.h"
#include "base/MediaMeta.h"
#include "base/SimplePool.h"
#include "core/NodeUtils.h"

namespace AVPipeline {

struct Writer;
using WriterSP = std::shared_ptr<Writer>;
struct Reader;
using ReaderSP = std::shared_ptr<Reader>;
struct PoolWriter;
struct INode {
    INode() = default;
    virtual ~INode() = default;

    struct NodeListener {
        NodeListener() = default;
        virtual ~NodeListener() = default;
        virtual void OnMessage(int, int, int, MediaParcelSP , const INode *) { }
        virtual void OnBuffer(int, MediaBufferSP, MediaType, const INode *) { }

    private:
        DISALLOW_COPY_AND_ASSIGN(NodeListener);
    };

    enum class State {
        UNINITIALIZED, // call deinit
        IDLE,          // call init/reset
        PREPARED,      // call prepare/stop
        STARTED,       // call start/resume
        PAUSED,        // call paused
        FLUSH_DONE,
        SEEK_DONE,
        EOS_DONE,
        MAX_COUNT
    };
    enum Event {
        EVENT_PREPARE_DONE,          // 0
        EVENT_START_DONE,            // 1
        EVENT_STOP_DONE,             // 2
        EVENT_PAUSE_DONE,            // 3
        EVENT_RESUME_DONE,           // 4
        EVENT_SEEK_DONE,             // 5
        EVENT_RESET_DONE,            // 6
        EVENT_FLUSH_DONE,            // 7
        EVENT_EOS,                   // 8
        EVENT_GOT_VIDEO_FORMAT,      // 9
        EVENT_MEDIA_DURATION,        // 10
        EVENT_BUFFERING_UPDATE,      // 11
        EVENT_ERROR,                 // 12
        EVENT_INFO,                  // 13
        EVENT_VIDEO_ROTATION_DEGREE, // 14
        EVENT_GET_TRACK_INFO_DONE,   // 15
        EVENT_OVER_RUN,              // 16
        EVENT_UNDER_RUN,             // 17
        EVENT_BUFFER,                // 18
        EVENT_MAX
    };

    enum EventInfo {
        INFO_VIDEO_RENDER_START,
        INFO_MEDIA_RENDER_STARTED,
        INFO_META_DATA_UPDATE,
        INFO_SEEKABLE,
        // for pre-defined filter cv algorithm
        INFO_CV_PREDEFINED_BEGIN = 0X100,
        INFO_CV_BODY_MASK = INFO_CV_PREDEFINED_BEGIN,
        INFO_CV_PREDEFINED_END = 0X1FF,

        // for pre-defined filter sound algorithm
        INFO_SOUND_PREDEFINED_BEGIN = 0X200,
        INFO_SOUND_SED = INFO_SOUND_PREDEFINED_BEGIN,
        INFO_SOUND_PREDEFINED_END = 0X2FF,

        // for use-defined filter cv algorithm
        INFO_CV_USE_DEFINED_BEGIN = 0X300,
        INFO_CV_USE_DEFINED_END = 0X3FF,

        // for use-defined filter sound algorithm
        INFO_SOUND_USE_DEFINED_BEGIN = 0X400,
        INFO_SOUND_USE_DEFINED_END = 0X4FF
    };

    virtual State GetState() const { return State::MAX_COUNT; }
    virtual const char *Name() const { return "UnknownNode"; }
    virtual const char *Version() const { return CORE_PLUGIN_VERSION; }
    virtual WriterSP GetWriter(MediaType);
    virtual RetCode AddDownLink(INode *, MediaType);
    virtual RetCode SetMetaData(const MediaMetaSP &, MediaType) { return ERROR_UNSUPPORTED; }
    virtual MediaMetaSP GetMetaData(MediaType) const { return nullptr; }
    virtual RetCode Write(const MediaBufferSP &, MediaType) { return ERROR_UNSUPPORTED; }
    virtual RetCode SetListener(std::weak_ptr<NodeListener> listener);
    virtual RetCode Init() { return OK; }
    virtual void DeInit() {}
    virtual RetCode SetParameter(const MediaMetaSP &) { return ERROR_UNSUPPORTED; }
    virtual RetCode GetParameter(MediaMetaSP &) const { return ERROR_UNSUPPORTED; }
    virtual RetCode Prepare(bool isAsync = true) { (void) isAsync; return OK; }
    virtual RetCode Start(){ return OK; }
    virtual RetCode Stop(){ return OK; }
    virtual RetCode Pause(){ return OK; }
    virtual RetCode Resume(){ return OK; }
    virtual RetCode Seek(int, int){ return OK; }
    virtual RetCode Reset(){ return OK; }
    virtual RetCode Flush(){ return OK; }

    virtual RetCode SetClock(ClockCoreSP) { return OK; }
    virtual ClockCoreSP ProvideClock() { return nullptr; }
    static const char *GetStateStr(State s);
    static const char *GetEventStr(Event event);
    static const char *GetMediaTypeStr(MediaType type);

    RetCode Notify(int msg, int param1, int param2, MediaParcelSP obj) const;
    RetCode NotifyBuffer(MediaBufferSP buffer, MediaType type) const;

protected:
    friend struct Writer;
    friend struct PoolWriter;
    virtual void OnGetBufferPoolConfig(MediaType type, uint32_t &count, int64_t &durationUs);
    virtual bool IsPaused() = 0;

protected:
    MediaType mMediaType { MediaType::MT_MAX };
    mutable WriterSP mLocalWriter { nullptr };
    WriterSP mDownLinkWriter { nullptr };
    NodeType mNodeType { NodeType::NT_MAX };

private:
    std::weak_ptr<NodeListener> mListener;
    DISALLOW_COPY_AND_ASSIGN(INode);
};
using NodeSP = std::shared_ptr<INode>;

template <typename D, typename = std::enable_if_t<std::is_base_of_v<INode, D>>, typename... TArgs>
INode *CreateNode(TArgs &&... args)
{
    INode *node = new (std::nothrow) D(std::forward<TArgs>(args)...);
    if (node == nullptr) {
        return nullptr;
    }
    RetCode ret = node->Init();
    if (ret != OK) {
        delete node;
        node = nullptr;
    }
    return node;
}

extern "C" void DestroyNode(INode *node);
} // namespace AVPipeline

#endif // INODE_H
