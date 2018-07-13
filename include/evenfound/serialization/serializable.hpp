#pragma once

#include <evenfound/buffer.hpp>


namespace NEvenFound::NSerialization {

struct ISerializable {
    virtual ~ISerializable() { }

    virtual void Save(TBuffer &buffer) const = 0;

    virtual void Load(const TBuffer &buffer) = 0;
};


}   // namespace NEvenFound::NSerialization
