#pragma once

#include <evenfound/message/base.hpp>


namespace NEvenFound::NMessage {

struct TShutdownMsg
    : public TMessageBase<TShutdownMsg> 
{
    EF_MESSAGE_META("com.evenfound.TShutdownMsg");

    TShutdownMsg() { }
};
EF_REGISTER_MESSAGE(TShutdownMsg);

};
