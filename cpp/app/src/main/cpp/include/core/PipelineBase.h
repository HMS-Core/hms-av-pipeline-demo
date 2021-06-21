/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of PipelineBase
 */
#ifndef PIPELINE_BASE_H
#define PIPELINE_BASE_H
#include <condition_variable>
#include <cstddef>
#include <cstdio>
#include <memory>
#include <set>
#include "core/INode.h"
#include "core/IPipeline.h"
#include "core/Writer.h"
#include "base/MsgQueueThread.h"
#include "base/MediaMeta.h"
#include "base/MMListener.h"
#include "base/ElapsedTimer.h"
#include "core/SourceNode.h"
#include "core/SinkNode.h"
#include "core/FilterNode.h"
#include "GraphParser.h"

namespace AVPipeline {
struct PipelineParamRefBase : HolderBase {
    PipelineParamRefBase(int msg, int param1, int param2, const INode *sender, const MediaParcelSP param)
        : mMsg(msg), mSender(sender), mParam(param), mParam1(param1), mParam2(param2)
    {}
    PipelineParamRefBase(int msg, const MediaBufferSP buffer, MediaType type, const INode *sender)
        : mMsg(msg), mBuffer(buffer), mMediaType(type), mSender(sender)
    {}
    int mMsg { 0 };
    MediaBufferSP mBuffer { nullptr };
    MediaType mMediaType { MT_MAX };
    const INode *mSender { nullptr };
    MediaParcelSP mParam { nullptr };
    int mParam1 { 0 };
    int mParam2 { 0 };
};

struct PipelineBase : IPipeline,
    MsgQueueThread,
    INode::NodeListener,
    GraphParser,
    std::enable_shared_from_this<PipelineBase> {
    static PipelineSP Create(PipelineBase *pipeline, std::weak_ptr<PipelineListener> listenerReceive);

    RetCode Prepare(bool isAsync) override;
    RetCode Start() override;
    RetCode Stop() override;
    RetCode Pause() override;
    RetCode Resume() override;
    RetCode Reset() override;
    RetCode Flush() override;
    RetCode GetState(INode::State &state) const override;
    RetCode SetParameter(const MediaMetaSP &) override;
    RetCode GetParameter(MediaMetaSP &) const override;
    RetCode WriteBuffer(const MediaBufferSP &buffer, MediaType type) override;
    void SetListener(std::weak_ptr<PipelineListener> listener) override;

    static void DebugMsgInfo(int event, int param1, const char *_sender = nullptr);
    ~PipelineBase() override = default;

protected:
    // can be override by subclass
    virtual RetCode DoInit() { return OK; }
    virtual void DoDeInit() {}
    virtual RetCode DoSetParameter(const MediaMetaSP &) { return OK; }
    virtual RetCode DoGetParameter(MediaMeta *) const;
    virtual RetCode DoStart() { return OK; }
    virtual RetCode DoResume() { return OK; }
    virtual RetCode DoStop() { return OK; }
    virtual RetCode DoPause() { return OK; }
    virtual RetCode DoPrepare() { return OK; }
    virtual RetCode DoReset() { return OK; }
    virtual RetCode DoFlush() { return OK; }
    virtual RetCode DoRegisterHandlers() { return OK; }
    virtual void DoNodeMessage(const MediaMetaSP &, uint32_t) { }
    virtual std::string GetGraphPath() { return mGraphPath; }
    virtual RetCode DoEosEvent() { return OK; }
    struct NodeInfo;
    virtual NodeSP DoAddNode(NodeInfo &);

protected:
    // can not be override
    explicit PipelineBase(bool isAsync = true);
    virtual RetCode DoPrepareGraph();
    void OnMessage(int msg, int param1, int param2, MediaParcelSP obj, const INode *sender) override final;
    void OnBuffer(int event, MediaBufferSP obj, MediaType type, const INode *sender) override final;
    NodeSP AddNode(NodeSP &up, int downId, std::map<int, GraphNodeInfo> &graph) final;
    std::vector<NodeSP> GetSourceNode() const override final;
    size_t GetSinkNodeSize() const override;
    std::vector<NodeSP> GetSinkNode(MediaType type) const override final;
    RetCode Notify(int msg, int param1, int param2, MediaParcelSP obj) const;
    RetCode Notify(MediaBufferSP buffer, MediaType type) const;
    RetCode LoadSourceNode(const std::string &libName, const std::string &mime);
    void SetState(INode::State &source, INode::State target);
    void SetErrorCode(uint32_t target);
    RetCode ProcessMessage(MsgType msg, bool isAsync);
    RetCode DoSetPipelineState(INode::Event event);
    bool DoCheckNodesState(const INode::Event &event, INode::State &stateTarget, const INode *sender);
    RetCode WaitNodeStateDone(INode::State &source, INode::State target, int64_t timeoutUs = -1);
    void Dump();

protected:
    struct NodeInfo {
        NodeInfo(NodeSP &comp, NodeType nt, MediaType mt, std::string mime, std::string libName = {})
            : mNode(comp), mNodeType(nt), mMediaType(mt), mMime(mime), mLibName(libName)
        {}
        NodeSP mNode { nullptr };
        NodeType mNodeType { NodeType::NT_MAX };
        MediaType mMediaType { MediaType::MT_MAX };
        std::string mMime {};
        std::string mLibName {};
        INode::State mState { INode::State::UNINITIALIZED };
        INode::State mStateOverlay { INode::State::UNINITIALIZED };

    private:
        NodeInfo() = delete;
    };

private:
    DECLARE_HANDLER(OnPrepare);
    DECLARE_HANDLER(OnSetParameter);
    DECLARE_HANDLER(OnGetParameter);
    DECLARE_HANDLER(OnStart);
    DECLARE_HANDLER(OnResume);
    DECLARE_HANDLER(OnPause);
    DECLARE_HANDLER(OnStop);
    DECLARE_HANDLER(OnFlush);
    DECLARE_HANDLER(OnReset);
    DECLARE_HANDLER(OnWriteBuffer);
    RetCode Init() override;
    void DeInit() override;
    static void Destroy(PipelineBase *pipeline);
    RetCode RegisterHandlers();
    void OnPipelineNotify(const MediaMetaSP &msg, uint32_t rspId);
    void OnNodeMessage(const MediaMetaSP &msg, uint32_t rspId);
    void SetPipelineState(INode::Event event, uint32_t rspId);
    static INode::State Event2State(INode::Event event);
    INode::State &GetNodeStateMode(INode::Event event, std::size_t i);
    INode::State &GetPipelineStateMode(INode::Event event);
    RetCode WaitPipelineStateDone(INode::Event event, INode::State target, int64_t timeoutUs = -1);

    DISALLOW_COPY_AND_ASSIGN(PipelineBase);

protected:
    friend struct GraphParser;
    std::weak_ptr<PipelineListener> mListenerSend;
    bool mIsAsync { true };
    INode::State mState { INode::State::UNINITIALIZED };
    INode::State mStateOverlay { INode::State::MAX_COUNT }; // help for Seek/flush/reset status check

    std::vector<NodeInfo> mNodes;
    mutable std::mutex mLock;
    std::condition_variable mCondition;

    uint32_t mErrorCode { 0 }; // setup the error code from msg handler thread
    MediaMetaSP mMediaMeta { nullptr };

    using StateAction = std::function<void()>;
    std::shared_ptr<MsgQueueThread> mNodeEventThread { nullptr };
    std::thread::id mNodeEventThreadId {};
    std::string mCoreXmlPath { CORE_XML_PATH };
    std::string mGraphPath {};
    std::set<std::string> mEosStream;
    bool mIsResetDone{false};
    bool mNodePrepareSyncMode{true};

    std::size_t mSourceIndex{UINT32_MAX};
    std::size_t mSinkClockIndex{UINT32_MAX}; // the sink node to get current playback position
    std::size_t mVideoSinkIndex{UINT32_MAX};
    std::string mVideoMime{};
    std::string mAudioMime{};
}; // PipelineBase

#define CHECK_AND_REPORT_RETURN_VOID(CHECK_VALUE, NOTIFY_EVENT)   \
    do {                                                          \
        if (CHECK_VALUE) {                                        \
            INFO("error %d", NOTIFY_EVENT);                       \
            Notify(INode::EVENT_ERROR, NOTIFY_EVENT, 0, nullptr); \
            return;                                               \
        }                                                         \
    } while (0)

#define CHECK_AND_REPORT_RETURN(CHECK_VALUE, NOTIFY_EVENT, RETURN_VALUE)   \
    do {                                                                   \
        if (CHECK_VALUE) {                                                 \
            INFO("%s check failed, error %d", #CHECK_VALUE, NOTIFY_EVENT); \
            Notify(INode::EVENT_ERROR, NOTIFY_EVENT, 0, nullptr);          \
            return RETURN_VALUE;                                           \
        }                                                                  \
    } while (0)
} // namespace AVPipeline

#endif // PIPELINE_BASE_H
