#pragma once

#include <string>
#include <evenfound/buffer.hpp>


namespace NEvenFound::NHelpers {

size_t ReadFile(const std::string &name, TBuffer &buffer);

}   // namespace NEvenFound
