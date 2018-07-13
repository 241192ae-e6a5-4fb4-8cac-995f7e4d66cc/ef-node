#pragma once

#include <filesystem>
#include <evenfound/exception.hpp>


namespace NEvenFound {


struct XInvalidKeyFile : public XGenericError {
    std::string Message;

    XInvalidKeyFile(const std::filesystem::path& path)
        : Message("NEvenFound::XInvalidKeyFile path=")
    {
        Message += path.string();
    }

    std::string String() const {
        return Message;
    }
};


}   // namespace NEvenFound
