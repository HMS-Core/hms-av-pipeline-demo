/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Description: header file of MediaMeta
 */
#ifndef MEDIA_META_H
#define MEDIA_META_H

#include <cstdint>
#include <map>
#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include "base/BaseMacros.h"
#include "base/HolderBase.h"
#include "base/MediaLiteAny.h"

#ifndef LOG_TAG
#define LOG_TAG "MediaMeta"
#endif

namespace AVPipeline {
struct MediaMeta;
using MediaMetaSP = std::shared_ptr<MediaMeta>;
struct MediaMeta : HolderBase {
    struct ByteBuffer {
        std::size_t size { 0 };
        uint8_t *data { nullptr };
    };

    struct Fraction {
        int32_t num;   // Numerator
        int32_t denom; // Denominator
        bool operator == (const Fraction &r) { return this->num == r.num && this->denom == r.denom; }
        const std::string ToString() { return std::to_string(num) + '/' + std::to_string(denom); }
    };

    struct Rect {
        int32_t left;
        int32_t top;
        int32_t right;
        int32_t bottom;
    };

    enum MetaType {
        MT_Invalid,
        MT_Bool,
        MT_Int8,
        MT_Int16,
        MT_Int32,
        MT_Int64,
        MT_Uint8,
        MT_Uint16,
        MT_Uint32,
        MT_Uint64,
        MT_Float,
        MT_Double,
        MT_Pointer,
        MT_String,
        MT_ByteBuffer,
        MT_Fraction,
        MT_Rect,
        MT_Object,
    };

    struct MetaItem;
    using MetaItemSP = std::shared_ptr<MetaItem>;
    struct MetaItem {
        static MetaItemSP Create();
        MetaItem();
        virtual ~MetaItem() = default;
        MetaType mType;
        ByteBuffer mByteBuffer;
        MediaLiteAny mAny;

    private:
        static void Destroy(MetaItem *item);
    };

    using MetaItemMap = std::map<std::string, MetaItemSP>;

    struct const_iterator {
        explicit const_iterator(MetaItemMap::const_iterator it);
        const_iterator(const const_iterator &another);
        const_iterator() = default;
        ~const_iterator();

        const_iterator &operator ++ ();
        const const_iterator operator ++ (int);
        const const_iterator &operator*();
        const std::string &key() const;
        const MetaItemSP &value() const;
        const_iterator &operator = (const const_iterator &another);
        bool operator != (const const_iterator &another);
        bool operator == (const const_iterator &another);

    private:
        friend struct MediaMeta;
        MetaItemMap::const_iterator &GetIterator() { return mMapIterator; }

    private:
        MetaItemMap::const_iterator mMapIterator;
    };
    using ConstIteratorSP = std::shared_ptr<const_iterator>;

    /* interfaces */
    static MediaMetaSP Create();
    MediaMetaSP Copy() const;

    /* merge items of mediaMeta to myself */
    bool Merge(const MediaMetaSP &mediaMeta);
    bool Merge(const MediaMeta &mediaMeta);

    void Dump(const char *prefix = nullptr) const;

    bool SetByteBuffer(const char *name, uint8_t *data, int32_t size);
    bool GetByteBuffer(const char *name, uint8_t *&data, int32_t &size) const;

    template <typename T> bool SetValue(const char *name, T value)
    {
        if (name == nullptr) {
            return false;
        }

        MetaType type = GetMetaType(typeid(value));
        if (type == MT_Invalid) {
            return false;
        }

        MetaItemSP meta;
        if (ContainsKey(name)) {
            if (mMetaItems[name]->mType != type) {
                return false;
            }
            meta = mMetaItems[name];
        } else {
            meta = MetaItem::Create();
            if (meta == nullptr) {
                return false;
            }
            meta->mType = type;
            mMetaItems[name] = meta;
        }

        mKeyType.push_back(name);
        mKeyType.push_back(GetMetaTypeName(typeid(value)));
        return meta->mAny.SetValue(value);
    }

    template <typename T> bool GetValue(const char *name, T &value) const
    {
        auto it = mMetaItems.find(name);
        if (it == mMetaItems.end()) {
            // TODO: add log here
            return false;
        }
        MetaType type = GetMetaType(typeid(value));
        if (type == MT_Invalid) {
            return false;
        }
        if (it->second->mType != type) {
            return false;
        }
        return it->second->mAny.GetValue(value);
    }

    const_iterator begin() const;
    const_iterator end() const;

    int32_t Size() const { return mMetaItems.size(); }
    bool Empty() const { return mMetaItems.empty(); }
    bool ContainsKey(const char *name) const;
    std::vector<std::string> GetKeyType() { return mKeyType; }

private:
    static MetaType GetMetaType(const std::type_info &type);
    static std::string GetMetaTypeName(const std::type_info &type);
    static void Destroy(MediaMeta *meta);

    MediaMeta() = default;
    ~MediaMeta() = default;

private:
    MetaItemMap mMetaItems {};
    std::vector<std::string> mKeyType;
    mutable ConstIteratorSP mBeginIterator { nullptr };
    mutable ConstIteratorSP mEndIterator { nullptr };

    DISALLOW_COPY_AND_ASSIGN(MediaMeta);
    DISALLOW_MOVE_AND_ASSIGN(MediaMeta);
};
} // namespace AVPipeline

#endif // MEDIA_META_H
