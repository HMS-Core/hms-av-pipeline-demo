/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of nodebase
 */
#ifndef NODE_BASE_H
#define NODE_BASE_H

#include <map>
#include <list>
#include <string>
#include "base/MMListener.h"
#include "core/INode.h"
#include "base/MediaMeta.h"
#include "base/SimplePool.h"
#include "base/MsgQueueThread.h"

namespace AVPipeline {
struct NodeBase : INode, MsgQueueThread {
    explicit NodeBase(const char *mime = nullptr, bool isProcThreadCreated = true, bool isAsync = true);
    ~NodeBase() override = default;
    const char *Name() const override { return "NodeBase"; }
    MediaMetaSP GetMetaData(MediaType type) const override;
    RetCode SetMetaData(const MediaMetaSP &metaData, MediaType type) override;
    RetCode AddDownLink(INode *node, MediaType mediaType) override;
    WriterSP GetWriter(MediaType type) override;
    RetCode Init() override;
    void DeInit() override;
    RetCode Prepare(bool isAsync) override;
    RetCode SetParameter(const MediaMetaSP &) override;
    RetCode GetParameter(MediaMetaSP &meta) const override;
    RetCode Start() override;
    RetCode Resume() override;
    RetCode Stop() override;
    RetCode Pause() override;
    RetCode Reset() override;
    RetCode Flush() override;

    static bool ReleaseBuffer(MediaBuffer *buffer);
    static MediaBufferSP CreateEosBuffer(MediaBuffer::BufferType type);
    static MediaType GetMediaType(const std::string &mime);

protected:
    virtual RetCode DoInit() { return OK; }
    virtual void DoDeInit() {}
    virtual RetCode DoPrepare() { return OK; }
    virtual RetCode DoSetParameter(const MediaMetaSP &) { return OK; }
    virtual RetCode DoGetParameter(MediaMeta *) const { return OK; }
    virtual RetCode DoStart() { return OK; }
    virtual RetCode DoResume() { return OK; }
    virtual RetCode DoStop() { return OK; }
    virtual RetCode DoPause() { return OK; }
    virtual RetCode DoReset() { return OK; }
    virtual RetCode DoFlush() { return OK; }
    virtual RetCode DoSetMetaData(const MediaMetaSP &, MediaType);
    virtual MediaMetaSP DoGetMetaData(MediaType) const;
    virtual RetCode DoAddDownLink(INode *, MediaType) { return OK; }
    virtual RetCode DoRegisterHandlers() { return OK; }
    virtual void TriggerRender(int64_t delayUs);
    virtual void NotifyOne();

    // buffer
    virtual RetCode DoProcessBuffer(MediaBufferSP &, std::vector<MediaBufferSP> &);
    virtual MediaBufferSP DoReadBuffer();
    virtual RetCode DoWriteBuffer(MediaBufferSP &out);
    virtual int64_t CalculateLatency(const MediaBufferSP &buffer);
    RetCode ProcessMessage(MsgType msg, bool isAsync);
    template <typename T> RetCode ProcessMessage(MsgType msg, T t, bool isAsync)
    {
        RetCode ret = OK;
        if (isAsync) {
            ret = PostMsg<T>(msg, t);
            if (ret != OK) {
                return ret;
            }
            return ASYNC_OK;
        }

        return SendMsg<T>(msg, t);
    }
    bool IsPaused() override { return mState != State::STARTED; }
    RetCode PauseInternel(MsgNotifyMode mode);
    State GetState() const override { return mState; }

protected:
    std::mutex mBaseLock;
    // subclass should create mOutputMetaData, which will be passed to downlink node
    MediaMetaSP mInputMetaData { nullptr };
    mutable MediaMetaSP mOutputMetaData { nullptr };
    State mState { State::UNINITIALIZED };

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
    DECLARE_HANDLER(OnRenderBuffer);
    void ProcessLoop();
    void DoBufferFlush();
    template <typename Action> RetCode DoAction(const Action &action);
    void StopProcessorThread();
    void CreateProcessorThread();
    virtual RetCode RegisterHandlers();

private:
    bool mFlushPending { false };
    bool mIsContinue { false };
    std::unique_ptr<std::thread> mProcessThread { nullptr };
    std::condition_variable mBaseCondition;
    bool mIsProcessorThreadCreated { true };
    bool mIsAsync { true };

private:
    DISALLOW_COPY_AND_ASSIGN(NodeBase);

};
} // namespace AVPipeline

#endif // NODE_BASE_H
