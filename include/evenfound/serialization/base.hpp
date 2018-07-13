#pragma once

#include <evenfound/buffer.hpp>
#include <evenfound/meta/typeinfo.hpp>
#include <evenfound/helpers/copy.hpp>


namespace NEvenFound::NSerialization {


/**
 *
 */
template <typename T>
struct TTypeSerializer {
    static size_t Store(uint8_t *dest, size_t offset, const T &src) {
        const size_t FieldSize = NMeta::TTypeInfo<T>::Size(src);
        NHelpers::Copy(dest + offset, &src, FieldSize);
        return offset + FieldSize;
    }

    static size_t Load(const uint8_t *src, size_t offset, T &dst) {
        const size_t FieldSize = NMeta::TTypeInfo<T>::Size(dst);
        NHelpers::Copy(&dst, src + offset, FieldSize);
        return offset + FieldSize;
    }
};


/**
 *
 */
template <typename TField, typename ... TFields>
struct TSerializer {
    static size_t BufferSize(const TField& field, const TFields& ...fields) {
        return NMeta::TTypeInfo<TField>::Size(field) + TSerializer<TFields...>::BufferSize(fields...);
    }

    static void Serialize(TBuffer &data, size_t offset, const TField& f, const TFields& ...fields) {
        offset = TTypeSerializer<TField>::Store(data.data(), offset, f);
        TSerializer<TFields...>::Serialize(data, offset, fields...);
    }

    static void Deserialize(const TBuffer &data, size_t offset, TField& f, TFields& ...fields) {
        offset = TTypeSerializer<TField>::Load(data.data(), offset, f);
        TSerializer<TFields...>::Deserialize(data, offset, fields...);
    }
};


/**
 *
 */
template <typename TField>
struct TSerializer<TField> {
    static size_t BufferSize(const TField& field) {
        return NMeta::TTypeInfo<TField>::Size(field);
    }

    static void Serialize(TBuffer &data, size_t offset, const TField& f) {
        TTypeSerializer<TField>::Store(data.data(), offset, f);
    }

    static void Deserialize(const TBuffer &data, size_t offset, TField& f) {
        TTypeSerializer<TField>::Load(data.data(), offset, f);
    }
};

}   // namespace NEvenFound::NSerialization
