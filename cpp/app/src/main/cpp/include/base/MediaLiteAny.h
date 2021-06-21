/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: head file of media lite any
 */
#ifndef MEDIA_LITE_ANY_H
#define MEDIA_LITE_ANY_H
#include <string.h>
#include <memory>
#include <typeinfo>
#include <iostream>
#include "BaseMacros.h"

namespace AVPipeline {
/*
 * Notice:
 * (1) the type save in MediaLiteAny MUST have USER-DEFINED function
 * for operator= and copy constructor if the DEFAULT one won't work well
 * (2) Value() interface is dangerous if the type of the interface
 * is not same to the real data, the result will not correct, maybe
 * we SHOULD throw std::bad_cast later
 */
struct MediaLiteAny {
    MediaLiteAny() = default;
    ~MediaLiteAny()
    {
        if (context != nullptr) {
            delete context;
        }
    }

    static std::shared_ptr<MediaLiteAny> Create()
    {
        MediaLiteAny *mediaAny = new (std::nothrow) MediaLiteAny();
        if (mediaAny == nullptr) {
            return nullptr;
        }
        return std::shared_ptr<MediaLiteAny>(mediaAny);
    }

    template <typename T> static std::shared_ptr<MediaLiteAny> Create(const T &value)
    {
        MediaLiteAny *mediaAny = new (std::nothrow) MediaLiteAny();
        if (mediaAny == nullptr) {
            return nullptr;
        }
        mediaAny->context = new (std::nothrow) Holder<T>(value);
        if (mediaAny->context == nullptr) {
            delete mediaAny;
            return nullptr;
        }
        return std::shared_ptr<MediaLiteAny>(mediaAny);
    }

    template <typename T> bool SetValue(const T &value)
    {
        DataHolder *cache = new (std::nothrow) Holder<T>(value);
        if (cache == nullptr) {
             return false;
        }
        if (context != nullptr) {
            delete context;
        }
        context = cache;
        return true;
    }

    template <typename T> const T Value() const
    {
        if (!strcmp(typeid(T).name(), GetTypeInfo().name())) {
            return static_cast<Holder<T> *>(context)->GetValue();
        } else {
            return T {};
        }
    }

    template <typename T> bool GetValue(T &value)
    {
        if (!context) {
            return false;
        }
        if (!strcmp(typeid(T).name(), GetTypeInfo().name())) {
            value = static_cast<Holder<T> *>(context)->GetValue();
            return true;
        } else {
            return false;
        }
    }

    const std::type_info &GetTypeInfo() const
    {
        if (context) {
            return context->GetTypeInfo();
        } else {
            return typeid(void);
        }
    }

private:
    struct DataHolder {
        DataHolder() = default;
        virtual ~DataHolder() = default;
        virtual const std::type_info &GetTypeInfo() const = 0;

    private:
        DISALLOW_COPY_AND_ASSIGN(DataHolder);
        DISALLOW_MOVE_AND_ASSIGN(DataHolder);
    };

    template <typename T> struct Holder : DataHolder {
        explicit Holder(const T &value) : DataHolder(), data(value) {}
        virtual ~Holder() = default;
        const T &GetValue() const { return data; }
        virtual const std::type_info &GetTypeInfo() const override { return typeid(T); }

    private:
        DISALLOW_COPY_AND_ASSIGN(Holder);
        DISALLOW_MOVE_AND_ASSIGN(Holder);
        const T data;
    };

    DataHolder *context { nullptr };

private:
    DISALLOW_COPY_AND_ASSIGN(MediaLiteAny);
    DISALLOW_MOVE_AND_ASSIGN(MediaLiteAny);
};
} // namespace AVPipeline
#endif