#pragma once

#include <evenfound/crypto/rsa.hpp>
#include <evenfound/network/session.hpp>
#include <evenfound/message/message_handler.hpp>


namespace NEvenFound {


class TNodeSessionBase
    : public NNetwork::TSession
{
    TRsaPrivateKey  PrivateKey;

    TRsaPublicKey   PublicKey;

public: /* Session Impl */
    using NNetwork::TSession::TSession;

    void OnAccepted();

    void OnRead(const TBuffer& buffer);

    void OnWritten(size_t size);

    void OnError(const boost::system::error_code& error);

    void OnClosed();

    void SendMessage(const TBuffer& buffer);

    template <class TMessage, typename ... Args>
    void SendMessage(Args&& ... args) {
        IMessagePtr Message = MakeMessage<TMessage>(std::forward<Args>(args)...);
        TBuffer Buffer;
        Message->Store(Buffer);
        SendMessage(Buffer);
    }


    void SetRsaPublicKey(const TRsaPublicKey& key) {
        PublicKey = key;
    }

    void SetRsaPrivateKey(const TRsaPrivateKey& key) {
        PrivateKey = key;
    }
public: /* */
    virtual void OnVerifiedMessage(IMessagePtr message) = 0;

    virtual void OnBadMessage(/* error code */) = 0;
};


template <class T, class ... TMessages>
class TNodeSession 
    : public TNodeSessionBase
    , public TMessageHandler<T, TMessages...>
{
    using TNodeSessionBase::TNodeSessionBase;

    void OnVerifiedMessage(IMessagePtr message) {
        TMessageHandler<T, TMessages...>::HandleMessage(message);
    }

    void OnBadMessage(/* error code */) {
        Close();
    }
};


}   // namespace TEvenFound
