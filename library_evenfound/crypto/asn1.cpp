#include <evenfound/crypto/asn1.hpp>

#include <string>
#include <iostream>

#include <evenfound/helpers/hex_string.hpp>

namespace NEvenFound {

namespace EAsnValueType {
    static constexpr uint8_t AVT_SEQUENCE = 0x30;
    static constexpr uint8_t AVT_INTEGER = 0x02;
}


/**
 *  @brief parse ASN.1 length field
 *  @return offset to next byte after length
 */
size_t Asn1ParseLength(const uint8_t *p, size_t offset, size_t max, size_t &length) {
    if (offset >= max) {
        length = 0;
        return max;
    }

    if (p[offset] & 0x80) {
        ////std::cerr << "Asn1ParseLength> multi-byte value" << std::endl;
        size_t LengthFieldSize = p[offset] & 0x7F;

        offset += 1;

        length = 0;
        while (LengthFieldSize > 0) {
            length <<= 8;
            length |= p[offset];

            LengthFieldSize -= 1;
            offset += 1;
        }
        return offset;
    } else {
        length = static_cast<size_t>(p[offset]);
        //std::cerr << "Asn1ParseLength> one-byte value, length=" << length << std::endl;
        offset += 1;
    }

    return offset;
}


/**
 *  @brief parse ASN.1 integer
 */
size_t Asn1ParseInteger(const uint8_t *p, size_t offset, size_t max, IAsnParserCallback *callback) {
    size_t IntegerLength = 0;

    offset = Asn1ParseLength(p, offset, max, IntegerLength);

    std::string IntegerValue = NHelpers::HexString(p + offset, IntegerLength);

    callback->OnInteger(TBigInteger(IntegerValue, 16));

    return offset + IntegerLength;
}


/**
 *  @brief parse ASN.1 sequence
 *  @param[in]  p           pointer to data
 *  @param[in]  offset      start offset
 *  @param[in]  max         data size
 *  @param[in]  callback    callback
 *  @return offset to next byte after sequence
 */
size_t Asn1ParseSequence(const uint8_t *p, size_t offset, size_t max, size_t level, IAsnParserCallback *callback) {
    size_t SequenceSize = 0;

    offset = Asn1ParseLength(p, offset, max, SequenceSize);
    const size_t SequenceEndOffset = offset + SequenceSize;

    //std::cerr << "Asn1ParseSequence> SequenceSize = " << SequenceSize << std::endl;
    //std::cerr << "Asn1ParseSequence> SequenceEnd = " << SequenceEndOffset << std::endl;

    if (max < offset) {
        // callback->OnError("overflow")
        // std::cerr << "Asn1ParseSequence> overflow" << std::endl;
        return max;
    }

    if (max - offset + 1 < SequenceSize) {
        // callback->OnError("not enought data")
        // std::cerr << "Asn1ParseSequence> not enought data" << std::endl;
        return max;
    }

    callback->OnSequenceBegin(level, SequenceSize);

    while (offset < SequenceEndOffset) {
        switch (p[offset]) {
            case EAsnValueType::AVT_SEQUENCE:
                //std::cerr << "Asn1ParseSequence> found nested sequence" << std::endl;
                offset = Asn1ParseSequence(p, offset + 1, max, level + 1, callback);
                break;

            case EAsnValueType::AVT_INTEGER:
                //std::cerr << "Asn1ParseSequence> found integer" << std::endl;
                offset = Asn1ParseInteger(p, offset + 1, max, callback);
                //std::cerr << "Asn1ParseSequence> next type " << static_cast<int>(p[offset]) << std::endl;
                break;

            default:
                //std::cerr << "Asn1ParseSequence> found unexpected type " << static_cast<int>(p[offset]) << std::endl;
                // callback->OnError("unexpected type")
                return max;
        }
    }


    callback->OnSequenceEnd(level);

    return offset;
}


/**
 *
 */
void Asn1Parse(const TBuffer& data, IAsnParserCallback *callback) {
    if (!callback) {
        return;
    }

    const size_t Size = data.Size();

    if (Size < 1) {
        // callback->OnError("no data");
        return;
    }

    const uint8_t *Data = data.Data();

    if (*Data != EAsnValueType::AVT_SEQUENCE) {
        // callback->OnError("expected sequence type got smth else");
        return;
    }

    Asn1ParseSequence(Data, 1, Size, 0, callback);
}


}   // namespace NEvenFound
