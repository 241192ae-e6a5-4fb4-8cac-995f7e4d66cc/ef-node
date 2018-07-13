#pragma once

#include <evenfound/message/base.hpp>


namespace NEvenFound::NMessage {

struct TTextMsg
    : public TMessageBase<TTextMsg> 
{
    EF_MESSAGE_META("com.evenfound.TTextMsg");

    std::string Payload;

    TTextMsg() { }

    TTextMsg(const std::string& payload)
        : Payload(payload)
    { }

    void Store(TBuffer &buffer) const {
        NSerialization::Store(buffer, MessageId, Payload);
    }

    void Load(const TBuffer &buffer) {
        NSerialization::Load(buffer, MessageId, Payload);
    }
};
EF_REGISTER_MESSAGE(TTextMsg);


};
