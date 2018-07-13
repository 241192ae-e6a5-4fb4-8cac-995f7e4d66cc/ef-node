#pragma once

#include <evenfound/message/base.hpp>


namespace NEvenFound::NMessage {

struct TPingMsg
    : public TMessageBase<TPingMsg> 
{
    EF_MESSAGE_META("com.evenfound.TPingMsg");

    std::string Payload;

    TPingMsg() { }

    TPingMsg(const std::string& payload)
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
