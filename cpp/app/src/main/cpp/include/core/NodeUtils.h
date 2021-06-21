/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of MMListener
 */
#ifndef NODE_UTILS_H
#define NODE_UTILS_H

namespace AVPipeline {
enum MsgType : uint32_t {
    MSG_PREPARE = 0,
    MSG_PREPARE_ASYNC,
    MSG_START,
    MSG_RESUME,
    MSG_PAUSE,
    MSG_STOP,
    MSG_FLUSH,
    MSG_SEEK,
    MSG_SET_PARAMETER,
    MSG_SET_PARAMETER_ASYNC,
    MSG_GET_PARAMETER,
    MSG_ADD_DOWN_LINK_NODE,
    MSG_SET_METADATA,
    MSG_RESET,
    MSG_ADD_DOWNLINK,
    MSG_RENDER_BUFFER,
    MSG_SOURCE_DEFINE = 0X100,
    MSG_FILTER_DEFINE = 0X200,
    MSG_SINK_DEFINE = 0X500,
    MSG_USER_DEFINE = 0X600
};

enum MediaType : uint32_t {
    MT_VIDEO,
    MT_AUDIO,
    MT_SUBTITLE,
    MT_MAX
};

enum class NodeType : uint32_t {
    NT_SOURCE = 0,
    NT_FILTER,
    NT_SINK,
    NT_MAX
};

enum MsgNotifyMode {
    ASYNC_NOTIFY_MODE,
    ASYNC_NOT_NOTIFY_MODE,
    SYNC_MODE,
    MODE_MAX
};

}
#endif