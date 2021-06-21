/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of holder base
 */
#ifndef HOLD_BASE_H
#define HOLD_BASE_H

#include <memory>
#include "base/MediaErrors.h"

namespace AVPipeline {
struct HolderBase {
    HolderBase() = default;
    virtual ~HolderBase() = default;
};
using HolderBaseSP = std::shared_ptr<HolderBase>;

}

#endif // HOLD_BASE_H
