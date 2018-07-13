#pragma once

#include <evenfound/message/base.hpp>


namespace NEvenFound {


template <class THandler, class TMessage, class ... TMessages>
struct TMessageHandlerBase
    : public TMessageHandlerBase<THandler, TMessage>
    , public TMessageHandlerBase<THandler, TMessages...>
{
    bool HandleMessage(IMessagePtr message) {
        const bool result = TMessageHandlerBase<THandler, TMessage>::HandleMessage(message);
        return result ? result : TMessageHandlerBase<THandler, TMessages...>::HandleMessage(message);
    }
};


template <class THandler, class TMessage>
struct TMessageHandlerBase<THandler, TMessage>
{
    virtual ~TMessageHandlerBase() { }

    bool HandleMessage(IMessagePtr message) {
        if (message->GetMessageId() == TMessage::CMessageType) {
            THandler& Handler = static_cast<THandler&>(*this);
            const TMessage& Message = *dynamic_cast<TMessage*>(message.get());
            Handler.OnMessage(Message);
            return true;
        }
        return false;
    }
};


template <class THandler, class ... TMessages>
struct TMessageHandler
    : public TMessageHandlerBase<THandler, TMessages...>
{
    virtual bool OnUnknownMessage(IMessagePtr) { return false; }

    bool HandleMessage(IMessagePtr message) {
        if(TMessageHandlerBase<THandler, TMessages...>::HandleMessage(message)) {
            return true;
        }
        return OnUnknownMessage(message);
    }
};

}
