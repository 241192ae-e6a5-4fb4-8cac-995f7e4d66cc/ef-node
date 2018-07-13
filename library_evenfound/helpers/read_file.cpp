#include <fstream>


#include <evenfound/helpers/read_file.hpp>


namespace NEvenFound::NHelpers {

size_t ReadFile(const std::string &name, TBuffer &buffer) {
    std::ifstream Stream(name.c_str(), std::ios::binary);
    if (!Stream) {
        return 0;
    }

    Stream.seekg(0, std::ios::end);
    const size_t Size = Stream.tellg();
    if (!Size) {
        return 0;
    }

    buffer.resize(Size);
    Stream.seekg(0, std::ios::beg);

    Stream.read(reinterpret_cast<char*>(buffer.Data()), buffer.Size());

    return Size;
}


}   // namespace NEvenFound
