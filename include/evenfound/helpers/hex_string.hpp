#pragma once

#include <cstdint>
#include <string>

namespace NEvenFound::NHelpers {

/**
 *
 */
std::string HexString(const uint8_t *data, size_t size);

/**
 *
 */
static inline std::string HexString(const char *data, size_t size) {
    return HexString(reinterpret_cast<const uint8_t*>(data), size);
}

}   // namespace NEvenFound::NHelpers
