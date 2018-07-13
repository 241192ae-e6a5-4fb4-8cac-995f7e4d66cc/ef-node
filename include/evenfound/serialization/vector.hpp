#pragma once

#include <evenfound/serialization/base.hpp>


namespace NEvenFound::NSerialization {


/**
 *
 */
template <typename T>
struct TTypeSerializer<std::vector<T>> {
    using TSizeInfo = NMeta::TTypeInfo<size_t>;

    /**
     *
     */
    static size_t Store(uint8_t *dest, size_t offset, const std::vector<T> &src) {
        const size_t Size = src.size();
        NHelpers::Copy(dest + offset, &Size, TSizeInfo::Size());

        if constexpr (NMeta::TTypeInfo<T>::ConstantSize) {
            NHelpers::Copy(dest + offset + TSizeInfo::Size(), src.data(), Size * NMeta::TTypeInfo<T>::Size());
            offset += TSizeInfo::Size() + Size * NMeta::TTypeInfo<T>::Size();
        } else {
            offset += TSizeInfo::Size();
            for (const T &value : src) {
                offset = TTypeSerializer<T>::Store(dest, offset, value);
            }
        }

        return offset;
    }

    /**
     *
     */
    static size_t Load(const uint8_t *src, size_t offset, std::vector<T> &dst) {
        size_t size = 0;
        NHelpers::Copy(&size, src + offset, NMeta::TTypeInfo<size_t>::Size());
        dst.reserve(size);

        offset += NMeta::TTypeInfo<size_t>::Size();

        if constexpr (NMeta::TTypeInfo<T>::ConstantSize) {
            dst.resize(size);
            NHelpers::Copy(dst.data(), src + offset, size * NMeta::TTypeInfo<T>::Size());
            offset += size * NMeta::TTypeInfo<T>::Size();
        } else {
            T value;
            for (size_t i = 0; i < size; ++i) {
                offset = TTypeSerializer<T>::Load(src, offset, value);
                dst.emplace_back(value);
            }
        }

        return offset; 
    }
};

}   // namespace NEvenFound::NSerialization
