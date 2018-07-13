#include <evenfound/helpers/copy.hpp>
#include <cstring>

namespace NEvenFound::NHelpers {


void Copy(void *dst, const void *src, size_t count) {
    ::memcpy(dst, src, count); 
}


}   //  namespace NEvenFound::NHelpers
