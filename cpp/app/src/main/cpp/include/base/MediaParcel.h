/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2017-2019. All rights reserved.
 * Description: header file of MediaParcel
 */

#ifndef MEDIA_PARCEL_H
#define MEDIA_PARCEL_H

#include <vector>
#include <string>
#include "base/HolderBase.h"
#include "base/MediaErrors.h"
#include "base/BaseMacros.h"

namespace AVPipeline {
struct MediaParcel : HolderBase {
    static std::shared_ptr<MediaParcel> Create();

    template <typename T> RetCode WriteValue(T val);
    template <typename T> RetCode ReadValue(T &val) const;
    RetCode WriteByteBuffer(const uint8_t *data, uint32_t size);
    const uint8_t *ReadByteBuffer(uint32_t size) const;
    RetCode WriteCString(const char *val);
    const char *ReadCString() const;
    int GetDataSize() const { return mDataWritePos; }

private:
    static void Destroy(MediaParcel *);
    MediaParcel() = default;
    ~MediaParcel() override = default;

private:
    constexpr static uint32_t DATA_SIZE_MAX = 32 * 1024;
    uint8_t *mData { nullptr };
    std::size_t mDataSize { DATA_SIZE_MAX };
    mutable std::size_t mDataWritePos { 0 };
    mutable std::size_t mDataReadPos { 0 };

    std::vector<std::string> mStrings {};
    mutable std::size_t mStringReadPos { 0 };

private:
    RetCode Init();
    void DeInit();

private:
    DISALLOW_COPY_AND_ASSIGN(MediaParcel);
    DISALLOW_MOVE_AND_ASSIGN(MediaParcel);
};

using MediaParcelSP = std::shared_ptr<MediaParcel>;
} // namespace AVPipeline

#endif // MEDIA_PARCEL_H
