/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Description: header file of check macros
 */

#ifndef CHECK_MARCOS_H
#define CHECK_MARCOS_H
#include "base/Log.h"

namespace AVPipeline {
/* defined for unused params */
#define UNUSED_PARAM(x) (void)(x)
#define TO_STRING(x) #x
#define PRINT_STRING(x) (x) == nullptr ? "null" : (x)
#define AV_NEW new (std::nothrow)

#define CHECK_COND_RETURN_VOID(condition)                                             \
    do {                                                                              \
        if (condition) {                                                              \
            ERROR("check(%s) error", TO_STRING(condition));                           \
            return;                                                                   \
        }                                                                             \
    } while (0)

#define CHECK_COND_RETURN(condition, retVal)                                          \
    do {                                                                              \
        if (condition) {                                                              \
            ERROR("check(%s) error", TO_STRING(condition));                           \
            return (retVal);                                                          \
        }                                                                             \
    } while (0)


#define CHECK_COND_RET_ERR(condition) CHECK_COND_RETURN(condition, ERROR_INVALID_OPERATION)

#define CHECK_NULL_PTR_RETURN(ptr, retVal) CHECK_COND_RETURN((ptr) == nullptr, (retVal))
#define CHECK_NULL_PTR_RETURN_VOID(ptr) CHECK_COND_RETURN_VOID((ptr) == nullptr)
#define CHECK_NULL_PTR_RETURN_ERR(ptr) CHECK_COND_RETURN((ptr) == nullptr, ERROR_INVALID_PARAM)

#define SET_PARAM_I32_GET_VAL(_meta, _key, _out_val)              \
    if (key == (_key)) {                                          \
        MM_ASSERT(item->mType == MediaMeta::MT_Int32);            \
        _out_val = item->mAny.Value<int32_t>();                   \
        INFO("setparam key: %s, val: %d", key.c_str(), _out_val); \
        (_meta)->SetValue<int32_t>((_key), (_out_val));           \
        continue;                                                 \
    }

#define SET_PARAM_I64_GET_VAL(_meta, _key, _out_val)                       \
    if (key == (_key)) {                                                   \
        MM_ASSERT(item->mType == MediaMeta::MT_Int64);                     \
        _out_val = item->mAny.Value<int64_t>();                            \
        INFO("setparam key: %s, val: %" PRId64 "", key.c_str(), _out_val); \
        (_meta)->SetValue<int32_t>((_key), (_out_val));                    \
        continue;                                                          \
    }

#define SET_PARAM_STRING_GET_VAL(_meta, _key, _out_val)                     \
    if (key == (_key)) {                                                    \
        MM_ASSERT(item->mType == MediaMeta::MT_String);                     \
        _out_val = item->mAny.Value<string>();                              \
        INFO("setparam key: %s, val: %s", key.c_str(), (_out_val).c_str()); \
        (_meta)->SetValue<string>((_key), (_out_val));                      \
        continue;                                                           \
    }

#define SET_PARAM_FlOAT(_meta, _key)                                                  \
    if (key == (_key)) {                                                              \
        MM_ASSERT(item->mType == MediaMeta::MT_Float);                                \
        (_meta)->SetValue<float>((_key), item->mAny.Value<float>());                  \
        MC_INFO("setparam key: %s, val: %f", key.c_str(), item->mAny.Value<float>()); \
        continue;                                                                     \
    }

#define SET_PARAM_I32(_meta, _key)                                                      \
    if (key == (_key)) {                                                                \
        MM_ASSERT(item->mType == MediaMeta::MT_Int32);                                  \
        (_meta)->SetValue<int32_t>((_key), item->mAny.Value<int32_t>());                \
        MC_INFO("setparam key: %s, val: %d", key.c_str(), item->mAny.Value<int32_t>()); \
        continue;                                                                       \
    }

#define SET_PARAM_POINTER(_meta, _key)                                                 \
    if (key == (_key)) {                                                               \
        MM_ASSERT(item->mType == MediaMeta::MT_Pointer);                               \
        (_meta)->SetValue<void *>((_key), item->mAny.Value<void *>());                 \
        MC_INFO("setparam key: %s, val: %p", key.c_str(), item->mAny.Value<void *>()); \
        continue;                                                                      \
    }

#define SET_PARAM_BUFFER(_meta, _key)                                                   \
    if (key == (_key)) {                                                                \
        MM_ASSERT(item->mType == MediaMeta::MT_ByteBuffer);                             \
        (_meta)->SetByteBuffer((_key), item->mByteBuffer.data, item->mByteBuffer.size); \
        MC_INFO("setparam key: %s, size: %zu", key.c_str(), item->mByteBuffer.size);    \
        continue;                                                                       \
    }

#define SET_PARAM_STRING(_meta, _key)                                                          \
    if (key == (_key)) {                                                                       \
        MM_ASSERT(item->mType == MediaMeta::MT_String);                                        \
        (_meta)->SetValue<string>((_key), item->mAny.Value<string>().c_str());                 \
        MC_INFO("setparam key: %s, val: %s", key.c_str(), item->mAny.Value<string>().c_str()); \
        continue;                                                                              \
    }
} // namespace AVPipeline

#endif /* CHECK_MARCOS_H */
