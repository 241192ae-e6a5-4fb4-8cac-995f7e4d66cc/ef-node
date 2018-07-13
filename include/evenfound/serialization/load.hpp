#pragma once

#include <evenfound/buffer.hpp>
#include <evenfound/serialization/base.hpp>


namespace NEvenFound::NSerialization {

template <typename ... TFields>
void Load(const TBuffer &buffer, TFields& ... fields) {
    TSerializer<TFields...>::Deserialize(buffer, 0, fields...);
}


}
