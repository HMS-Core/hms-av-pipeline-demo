/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2017-2019. All rights reserved.
 * Description: header file of message queue thread
 */

#ifndef MSG_QUEUE_THREAD_H
#define MSG_QUEUE_THREAD_H

#include <list>
#include <map>
#include <functional>
#include <cassert>
#include <sys/time.h>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <utility>
#include "MediaMeta.h"
#include "base/HolderBase.h"
#include "base/MediaMeta.h"
#include "base/MediaErrors.h"

namespace AVPipeline {
static const char *MSG_WHAT = "what";

const static char *KEY_PARAM1 = "param1";
const static char *KEY_PARAM2 = "param2";
using MsgHandler = std::function<void(const MediaMetaSP &msg, uint32_t rspId)>;
struct MsgQueueThread {
public:
    explicit MsgQueueThread(const char *threadName);
    virtual ~MsgQueueThread();
    void PrepareToRun();
    void ExitToRun();
    void Flush();
    void RemoveMessage(uint32_t msgIdx);
    std::thread::id GetThreadId();

    // msg with no param
    RetCode PostMsg(uint32_t what, int64_t delayUs = 0);
    // msg with param1
    template <typename T> RetCode PostMsg(uint32_t what, T param, int64_t delayUs = 0)
    {
        MediaMetaSP msg = MediaMeta::Create();
        if (msg == nullptr) {
            return ERROR_NO_MEM;
        }
        msg->SetValue<uint32_t>(MSG_WHAT, what);
        msg->SetValue<T>(KEY_PARAM1, param);
        return ProcessMsg(msg, delayUs, 0);
    }
    // msg with more than one param, packaging in msg
    RetCode PostMsg(const MediaMetaSP &msg, int64_t delayUs = 0);

    // msg with no param, return RetCode
    RetCode SendMsg(uint32_t what, int64_t delayUs = 0);
    // msg with no param, return RetCode and other results
    RetCode SendMsg(uint32_t what, MediaMetaSP &out, int64_t delayUs = 0);
    // msg with param1, return RetCode
    template <typename T> RetCode SendMsg(uint32_t what, T param, int64_t delayUs = 0)
    {
        MediaMetaSP out = nullptr;
        RetCode ret = SendMsg<T>(what, param, out, delayUs);
        if (ret != OK) {
            return ret;
        }
        if (out == nullptr) {
            return ERROR_UNKNOWN;
        }
        if (!out->GetValue<int32_t>("ret", ret)) {
            return ERROR_UNKNOWN;
        }
        return ret;
    }
    // msg with param1, return RetCode and other results
    template <typename T> RetCode SendMsg(uint32_t what, T param, MediaMetaSP &out, int64_t delayUs = 0)
    {
        MediaMetaSP msg = MediaMeta::Create();
        if (msg == nullptr) {
            return ERROR_NO_MEM;
        }
        msg->SetValue<uint32_t>(MSG_WHAT, what);
        msg->SetValue<T>(KEY_PARAM1, param);
        return SendMsg(msg, out, delayUs);
    }
    // msg with more than one param, packaging in msg, return RetCode or other results
    RetCode SendMsg(const MediaMetaSP &msg, MediaMetaSP &out, int64_t delayUs = 0);

    RetCode RegisterHandler(uint32_t msg, MsgHandler handler);
    void SetThreadName(const char *name) { mThreadName = name; }

protected:
    RetCode PostReply(uint32_t respId, MediaMetaSP &msg);
    RetCode PostReplyHelper(uint32_t replyId, RetCode ret);

protected:
    static int64_t GetTimeUs();

private:
    RetCode ProcessMsg(const MediaMetaSP &msg, int64_t delayUs, uint32_t responseId);
    uint32_t GetReplyId();
    void MainLoop();

    struct MsgInfo {
        uint32_t rspId;
        int64_t whenUs;
        MediaMetaSP meta;
        MsgInfo(uint32_t id, int64_t when, MediaMetaSP msg) : rspId(id), whenUs(when), meta(std::move(msg)) {}
    };
    using MsgInfoSP = std::shared_ptr<MsgInfo>;

private:
    bool mContinue { false };

    std::mutex mMsgLock;
    std::condition_variable mMsgCond;
    std::list<MsgInfoSP> mMsgQueue;

    std::condition_variable mReplyCond;
    std::map<uint32_t, MediaMetaSP> mRespMap;
    uint32_t mCurRespId { 0 };
    std::thread mThread {};
    std::string mThreadName {};
    std::map<int, MsgHandler> mHandlers;
};

#define DECLARE_HANDLER(handler) void handler(const MediaMetaSP &msg, uint32_t rspId);
} // namespace AVPipeline
#endif // MSG_QUEUE_THREAD_H
