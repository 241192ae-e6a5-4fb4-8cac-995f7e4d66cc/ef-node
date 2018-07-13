#include <evenfound/helpers/hex_string.hpp>

#include <cstdint>
#include <string>

namespace NEvenFound::NHelpers {


std::string HexString(const uint8_t *data, size_t size) {
    std::string Result;
    Result.reserve(size * 2);

    for (size_t i = 0; i < size; ++i) {
        const uint8_t Byte = data[i];

        //std::cerr << "Asn1ParseInteger> I=" << i << " BYTE=" << static_cast<int>(Byte) << std::endl;

        const uint8_t HiValue = Byte >> 4;
        const uint8_t LoValue = Byte & 0x0F;
        const char HiChar = HiValue < 10 ? 0x30 + HiValue : 'a' + HiValue - 10;
        const char LoChar = LoValue < 10 ? 0x30 + LoValue : 'a' + LoValue - 10;

        Result.push_back(HiChar);
        Result.push_back(LoChar);
    }

    return Result;
}


}   // namespace NEvenFound::NHelpers
