/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of FilterNode
 */
#ifndef AVPIPELINE_FILTER_NODE_H
#define AVPIPELINE_FILTER_NODE_H

#include "core/NodeBase.h"
namespace AVPipeline {
struct FilterNode : NodeBase {
    FilterNode(const char *mime, bool isProcessorThread, bool isAsync) : NodeBase(mime, isProcessorThread, isAsync) {}
    ~FilterNode() override = default;
    const char *Name() const override { return "FilterNode"; }

private:
    DISALLOW_COPY_AND_ASSIGN(FilterNode);
};
}

#endif // AVPIPELINE_FILTER_NODE_H
