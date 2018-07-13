#pragma once

#include <evenfound/buffer.hpp>


namespace NEvenFound::NSerialization {

template <typename ... TFields>
void Store(TBuffer &buffer, TFields&& ...) {
    (void)buffer;
}


}
