#pragma once

#include <evenfound/math/bigint.hpp>
#include <evenfound/meta/crc64.hpp>


namespace NEvenFound {

struct TCrc64HashAlgorithm {
    static TBigInteger Calculate(const uint8_t *data, size_t size) {
        return TBigInteger(NMeta::NImpl::CRC64(reinterpret_cast<const char*>(data), size, 0));
    }
};
    
}   // namespace NEvenFound
