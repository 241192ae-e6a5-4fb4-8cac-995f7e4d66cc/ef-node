#pragma once

#include <cstdlib>
#include <cstdint>


#include <evenfound/buffer.hpp>
#include <evenfound/math/bigint.hpp>


namespace NEvenFound {

struct IAsnParserCallback {
    virtual void OnSequenceBegin(int level, size_t size) = 0;

    virtual void OnInteger(TBigInteger value) = 0;

    virtual void OnSequenceEnd(int level) = 0;
};


void Asn1Parse(const TBuffer& data, IAsnParserCallback *callback);


}   // namespace NEvenFound
