#pragma once

#include <evenfound/serialization/base.hpp>


namespace NEvenFound::NSerialization {

template <typename ... TFields>
void Store(TBuffer &buffer, const TFields& ... fields) {
    buffer.Resize(TSerializer<TFields...>::BufferSize(fields...));
    TSerializer<TFields...>::Serialize(buffer, 0, fields...);
}


}
