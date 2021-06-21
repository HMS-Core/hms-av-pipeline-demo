/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of media buffer
 */
#ifndef MEDIA_BUFFER_H
#define MEDIA_BUFFER_H
#include <functional>
#include <vector>
#include <cstdint>
#include "base/MediaMeta.h"

namespace AVPipeline {
struct MediaBuffer;
using MediaBufferSP = std::shared_ptr<MediaBuffer>;
struct MediaBuffer {
    constexpr static int MAX_DATA_PLANE = 8;
    constexpr static int MAX_RELEASE_FUNC_COUNT = 8;

    using releaseBufferFunc = std::function<bool(MediaBuffer *)>;
    enum BufferType {
        BT_Undefined,
        BT_ByteBuffer,  // compressed data
        BT_RawVideo,    // raw video frame data
        BT_BufferIndex, // buffer index for MediaCodec
        BT_RawAudio,    // raw audio data
        BT_MAX,
    };

    enum BufferFlag : uint64_t {
        BF_EOS = 1,
        BF_KeyFrame = 2,
        BF_CodecData = 4,  // for example, H264 SPS/PPS
        BF_AVPacket = 8,   // it is initialized from ffmpeg AVPacket, it is possible to retrieve the AVPacket by FFmpegHelper
        BF_AVFrame = 16,   // it is initialized from ffmpeg AVFrame, it is possible to retrieve the AVFrame by FFmpegHelper
        BF_MAX,
    };

    static MediaBufferSP Create(BufferType type = BT_ByteBuffer);
    inline BufferType Type() const { return mType; }
    inline void SetFlag(BufferFlag flag) { mFlags |= static_cast<unsigned int>(flag); }
    inline bool IsFlagSet(BufferFlag flag) const { return mFlags & static_cast<unsigned int>(flag); }

    bool SetBufferInfo(const uintptr_t* buffers,
                       const int32_t* offsets,
                       const int32_t* strides,
                       uint32_t dimension);
    bool GetBufferInfo(uintptr_t* buffers, int32_t* offsets, int32_t* strides, uint32_t dimension) const;
    bool UpdateBufferOffset(const int32_t* offsets, uint32_t dimension);

    inline void SetSize(int64_t size) { mSize = size; }
    inline int64_t Size() const { return mSize; }
    inline void SetDts(int64_t dts) { mDts = dts; }
    inline int64_t Dts() const { return mDts; }
    inline void SetPts(int64_t pts) { mPts = pts; }
    inline int64_t Pts() const { return mPts; }

    // based on us
    inline void SetDuration(int64_t duration) { mDuration = duration; }
    inline int64_t Duration() const { return mDuration; }

    // when one buffer want to continue the life of another one(usually reincarnation from former one by some
    // processing), specify the born time for it
    inline void SetBirthTimeInMs(int64_t birthTime) { mBirthTime = birthTime; }
    inline int64_t BirthTimeInMs() const { return mBirthTime; }
    // in us
    int64_t Age() const;

    bool AddReleaseBufferFunc(releaseBufferFunc releaseFunc);
    MediaMetaSP GetMediaMeta() const;

private:
    static void Destroy(MediaBuffer *p);
    RetCode Init();
    void DeInit();
    explicit MediaBuffer(BufferType type);
    ~MediaBuffer() = default;

private:
    DISALLOW_COPY_AND_ASSIGN(MediaBuffer);

private:
    BufferType mType { BT_ByteBuffer };
    uint64_t mFlags { 0 };
    bool mInit { false };

    int64_t mDuration { -1LL };
    std::vector<uintptr_t> mBuffers;
    std::vector<int32_t> mOffsets;
    std::vector<int32_t> mStrides;

    int64_t mSize { -1LL };
    int64_t mDts { -1LL };
    int64_t mPts { -1LL };
    int64_t mBirthTime { -1LL }; // debug use
    mutable MediaMetaSP mMeta { nullptr };

    std::vector<releaseBufferFunc> mReleaseFunc;
    int32_t mReleaseFuncCount { 0 };
};
} // end of namespace AVPipeline

#endif // MEDIA_BUFFER_H
