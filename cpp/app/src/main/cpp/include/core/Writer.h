/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of writer
 */
#ifndef WRITER_H
#define WRITER_H
#include "base/MediaBuffer.h"
#include "base/MediaMeta.h"
#include "base/SimplePool.h"
#include "base/CheckMacros.h"
#include "base/MediaErrors.h"

namespace AVPipeline {
struct INode;
enum MediaType : uint32_t;
struct Writer {
    Writer(MediaType type) : mType(type) {}
    Writer(INode *node, MediaType type) : mNode(node), mType(type) {}
    virtual ~Writer() = default;
    virtual RetCode Write(const MediaBufferSP &buffer, int64_t timeoutUs = -1LL);
    virtual RetCode SetMetaData(const MediaMetaSP &metaData);
    virtual MediaBufferSP Read(int64_t) { return nullptr; }
    virtual void WakeUp() {}
    virtual void Reset() {}
    virtual bool IsOverRun() const  { return false; }
    virtual bool IsUnderRun() const { return false; }
    virtual void Flush() {}
    virtual size_t Size() const { return 0; }

protected:
    virtual void Configure() {}

protected:
    bool mIsConfigured { false };
    INode *mNode { nullptr };
    MediaType mType;
};

struct PoolWriter : Writer, private SimplePool {
    PoolWriter(MediaType type);
    PoolWriter(INode *node, MediaType type);
    ~PoolWriter() override;
    RetCode Write(const MediaBufferSP &buffer, int64_t timeoutUs = -1LL) override;
    MediaBufferSP Read(int64_t timeoutUs) override;
    void WakeUp() override { SimplePool::WakeUp(); }
    void Reset() override { SimplePool::Reset(); }
    bool IsOverRun() const override { return SimplePool::IsOverRun(); }
    bool IsUnderRun() const override { return SimplePool::IsUnderRun(); }
    void Flush() override { SimplePool::Flush(); }
    size_t Size() const override { return SimplePool::Size(); }

private:
    void Configure() override;
};
using WriterSP = std::shared_ptr<Writer>;
} // namespace AVPipeline

#endif // WRITER_H
