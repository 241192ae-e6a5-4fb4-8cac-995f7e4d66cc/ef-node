#pragma once

#include <cstdint>
#include <string>


struct TNodeSettings {
    uint16_t Port;

    std::string MyPrivateKeyPath;

    std::string OtherPublicKeyPath;

    std::string RemoteAddress;

    uint16_t    RemotePort;

    TNodeSettings(int, char **);
};
