/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of media errors
 */
#ifndef MEDIA_ERRORS_H
#define MEDIA_ERRORS_H

#include <cerrno>
#include <cstdint>

namespace AVPipeline {
using RetCode = int32_t; // Error Code Type

enum {
    OK = 0,
    NO_ERROR = OK,
    ERROR_NO_MEM = -ENOMEM,
    ERROR_INVALID_OPERATION = -ENOSYS,
    ERROR_BAD_VALUE = -EINVAL,
    ERROR_NAME_NOT_FOUND = -ENOENT,
    ERROR_PERMISSION_DENIED = -EPERM,
    ERROR_NO_INIT = -ENODEV,
    ERROR_ALREADY_EXISTS = -EEXIST,
    ERROR_DEAD_OBJECT = -EPIPE,

    ERROR_BAD_INDEX = -EOVERFLOW,
    ERROR_NOT_ENOUGH_DATA = -ENODATA,
    ERROR_WOULD_BLOCK = -EWOULDBLOCK,
    ERROR_TIMED_OUT = -ETIMEDOUT,
    ERROR_UNKNOWN_TRANSACTION = -EBADMSG,

    ERROR_UNKNOWN = INT32_MIN, // -2147483648
    ERROR_BAD_TYPE = (ERROR_UNKNOWN + 1),
    ERROR_INVALID_PARAM,
    ERROR_NOT_INITED, // -2147483645
    ERROR_UNSUPPORTED,
    ERROR_NO_SUCH_FILE,
    ERROR_FILE_NO_SPACE_ON_DEVICE,
    ERROR_RESOURCE_LIMIT,
    ERROR_INVALID_STATE, // -2147483640
    ERROR_ALREADY_STATE,
    ERROR_CONNECTION_FAILED,
    ERROR_OP_FAILED,
    ERROR_NO_MORE,
    ERROR_IO, // -2147483635
    ERROR_MALFORMED,
    ERROR_FATAL_ERROR,
    ERROR_NO_NODE,
    ERROR_NO_MEDIA_TYPE,
    ERROR_NO_MEDIA_TRACK, // -2147483630
    ERROR_FULL,
    ERROR_EOS,
    ERROR_NODE_CONNECT_FAILED,
    ERROR_INTERRUPTED,
    ERROR_AGAIN, // -2147483625
    ERROR_NO_AUDIORENDER,
    ERROR_NO_AUDIODECODER,
    ERROR_NO_VIDEODECODER,
    ERROR_NOTEXISTS,
    ERROR_CODEC_ERROR, // -2147483620
    ERROR_AUDIO_DECODE,

    ERROR_FORMAT_CHANGED,
    ERROR_OUT_BUFFER_CHANGED,
    ERROR_NOT_SUPPORTED_FILE,
    ERROR_OVERRUN,  // -2147483615
    ERROR_UNDERRUN, // -2147483614

    ASYNC_OK = -1000
};
} // namespace AVPipeline
#endif // MEDIA_ERRORS_H
