#pragma once

#include <evenfound/message/base.hpp>


namespace NEvenFound::NMessage {

struct TPongMsg
    : public TMessageBase<TPongMsg> 
{
    EF_MESSAGE_META("com.evenfound.TPongMsg");

    std::string Payload;

    TPongMsg() { }

    TPongMsg(const std::string& payload)
        : Payload(payload)
    { }

    void Store(TBuffer &buffer) const {
        NSerialization::Store(buffer, MessageId, Payload);
    }

    void Load(const TBuffer &buffer) {
        NSerialization::Load(buffer, MessageId, Payload);
    }
};

};
