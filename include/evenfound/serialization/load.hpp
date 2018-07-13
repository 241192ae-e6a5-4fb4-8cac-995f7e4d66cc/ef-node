#pragma once

#include <evenfound/buffer.hpp>


namespace NEvenFound::NSerialization {

template <typename ... TFields>
void Load(const TBuffer &buffer, TFields&& ...) {
    (void)buffer;
}


}
