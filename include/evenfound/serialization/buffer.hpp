#pragma once

#include <evenfound/serialization/base.hpp>
#include <iostream>


namespace NEvenFound::NSerialization {


/**
 *
 */
template <>
struct TTypeSerializer<::NEvenFound::TBuffer> {
    using TSizeInfo = NMeta::TTypeInfo<size_t>;

    /**
     *
     */
    static size_t Store(uint8_t *dest, size_t offset, const TBuffer& src) {
        //std::cerr << "STORE TBUFFER " << (void*)dest << " OFFSET " << offset << std::endl;
        const size_t Size = src.Size();
        NHelpers::Copy(dest + offset, &Size, TSizeInfo::Size());
        NHelpers::Copy(dest + offset + TSizeInfo::Size(), src.Data(), Size);
        return offset + TSizeInfo::Size() + Size;
    }

    /**
     *
     */
    static size_t Load(const uint8_t *src, size_t offset, TBuffer& dst) {
        size_t Size = 0;
        NHelpers::Copy(&Size, src + offset, TSizeInfo::Size());
        //std::cerr << "LOAD TBUFFER " << (void*)src << " OFFSET " << offset << std::endl;
        dst.Resize(Size);
        NHelpers::Copy(dst.data(), src + offset + TSizeInfo::Size(), Size);
        return offset + TSizeInfo::Size() + Size;
    }
};

}   // namespace NEvenFound::NSerialization
