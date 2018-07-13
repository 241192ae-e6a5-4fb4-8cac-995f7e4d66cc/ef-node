#pragma once

#include <evenfound/serialization/base.hpp>


namespace NEvenFound::NSerialization {


/**
 *
 */
template <>
struct TTypeSerializer<std::string> {
    static size_t Store(uint8_t *dest, size_t offset, const std::string &src) {
        const size_t Size = src.size();

        NHelpers::Copy(dest + offset, &Size, NMeta::TTypeInfo<size_t>::Size());
        NHelpers::Copy(dest + offset + NMeta::TTypeInfo<size_t>::Size(), src.data(), Size);
        return offset + NMeta::TTypeInfo<size_t>::Size() + Size;
    }

    static size_t Load(const uint8_t *src, size_t offset, std::string &dst) {
        size_t size = 0;
        NHelpers::Copy(&size, src + offset, NMeta::TTypeInfo<size_t>::Size());

        offset += NMeta::TTypeInfo<size_t>::Size();

        dst.resize(size);
        NHelpers::Copy(dst.data(), src + offset, size);

        return offset + size;
    }
};


}   // namespace NEvenFound::NSerialization
