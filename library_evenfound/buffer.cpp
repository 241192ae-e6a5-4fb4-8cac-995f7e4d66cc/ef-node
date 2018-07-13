#include <evenfound/buffer.hpp>
#include <evenfound/helpers/hex_string.hpp>


namespace NEvenFound {


std::string TBuffer::HexString() const {
    return NHelpers::HexString(Data(), Size());
}


}   // namespace NEvenFound
