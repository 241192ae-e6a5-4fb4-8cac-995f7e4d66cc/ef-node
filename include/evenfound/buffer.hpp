#pragma once

#include <cstdint>
#include <vector>
#include <string>


namespace NEvenFound {


/**
 *  @brief storage for bytes
 */
class TBuffer : public std::vector<uint8_t> {
public:
    using TBaseType = std::vector<uint8_t>;

    using TBaseType::TBaseType;

    inline const uint8_t* Data() const {
        return reinterpret_cast<const uint8_t*>(data());
    }

    inline uint8_t* Data() {
        return reinterpret_cast<uint8_t*>(data());
    }

    inline size_t Size() const {
        return size();
    }

    inline void Resize(size_t size) {
        this->resize(size);
    }

    inline void Reserve(size_t size) {
        this->reserve(size);
    }

    inline size_t Allocated() const {
        return capacity();
    }

    std::string HexString() const;
};


}   // namespace NEvenFound
