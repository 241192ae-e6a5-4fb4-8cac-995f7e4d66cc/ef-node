#pragma once

#include <evenfound/crypto/rsa.hpp>
#include <evenfound/network/session.hpp>
#include <evenfound/network/client.hpp>
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


/**
 *
 */
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


/**
 *
 */
struct INodeClientCallback {
    virtual ~INodeClientCallback() { }

    virtual void OnNodeConnected() = 0;

    virtual void OnNodeDisconnected() = 0;

    virtual void OnNodeMessageSent() = 0;
    
    virtual void OnNodeConnectionError() = 0;

    virtual void OnNodeError() = 0;
};

using INodeClientCallbackPtr = std::shared_ptr<INodeClientCallback>;


/**
 *
 */
class TNodeClient 
    : public NNetwork::TTcpClient
{
    TRsaPrivateKey          PrivateKey;

    TRsaPublicKey           PublicKey;

    INodeClientCallbackPtr  Callback;

public:
    using NNetwork::TTcpClient::TTcpClient;

    void OnClientConnected();

    void OnClientRead(const TBuffer& buffer);

    void OnClientWritten(size_t size);

    void OnClientError(const boost::system::error_code& error);

    void OnClientClosed();

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

    void SetCallback(INodeClientCallbackPtr callback) {
        Callback = callback;
    }
};


}   // namespace TEvenFound
