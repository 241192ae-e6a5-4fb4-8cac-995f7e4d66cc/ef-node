#pragma once

#include <boost/system/error_code.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <evenfound/buffer.hpp>


namespace NEvenFound::NNetwork {


struct ISession {
    virtual ~ISession() { }

    virtual void AsyncWrite(const TBuffer &buffer) = 0;

    virtual void AsyncRead(size_t min) = 0;

    virtual void Close() = 0;

    virtual void OnAccepted() = 0;

    virtual void OnRead(const TBuffer &buffer) = 0;

    virtual void OnWritten(size_t size) = 0;

    virtual void OnError(const boost::system::error_code &error) = 0;

    virtual void OnClosed() = 0;
};

using ISessionPtr = std::shared_ptr<ISession>;


struct ISessionFactory {
    virtual ~ISessionFactory() { }

    virtual ISessionPtr CreateSession(boost::asio::ip::tcp::socket &socket) = 0;
};

using ISessionFactoryPtr = std::shared_ptr<ISessionFactory>;


template <class TSession>
struct TSimpleSessionFactory
    : public ISessionFactory
{
    ISessionPtr CreateSession(boost::asio::ip::tcp::socket &socket) {
        return std::make_shared<TSession>(socket);
    }
};


class TSession 
    : public ISession
    , public std::enable_shared_from_this<TSession>
{
    boost::asio::ip::tcp::socket Socket;

    TBuffer RxBuffer;

    TBuffer TxBuffer;

public:
    TSession(boost::asio::ip::tcp::socket &socket)
        : Socket(std::move(socket))
    { }

    void AsyncWrite(const TBuffer &buffer);

    void AsyncRead(size_t min);

    void Close();

private:
    void InternalOnRead(const boost::system::error_code &error, size_t size);
    void InternalOnWritten(const boost::system::error_code &error, size_t size);
};


}   // namespace NEvenFound::NNetwork
