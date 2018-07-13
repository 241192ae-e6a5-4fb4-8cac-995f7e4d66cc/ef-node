#pragma once

#include <string>


namespace NEvenFound {


class XGenericError {
public:
    XGenericError() { }

    virtual ~XGenericError() { }

    virtual std::string String() const {
        return "NEvenFound::XGenericError";
    }
};


}   // namespace NEvenFound
