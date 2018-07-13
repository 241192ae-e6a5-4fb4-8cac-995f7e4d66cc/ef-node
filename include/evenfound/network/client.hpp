#pragma once

#include <evenfound/buffer.hpp>

#include <boost/system/error_code.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>

namespace NEvenFound::NNetwork {


/**
 *
 */
struct ITcpClient {
    virtual ~ITcpClient() { }

    virtual void AsyncConnect(const std::string &addr, uint16_t port) = 0;

    virtual void AsyncWrite(const TBuffer &buffer) = 0;

    virtual void AsyncRead(size_t min) = 0;

    virtual void Close() = 0;

    virtual void OnClientConnected() = 0;

    virtual void OnClientClosed() = 0;

    virtual void OnClientWritten(size_t size) = 0;

    virtual void OnClientError(const boost::system::error_code &error) = 0;

    virtual void OnClientRead(const TBuffer &buffer) = 0;
};

using ITcpClientPtr = std::shared_ptr<ITcpClient>;


/**
 *
 */
class TTcpClient 
    : public ITcpClient
    , public std::enable_shared_from_this<TTcpClient>
{
    boost::asio::ip::tcp::socket    Socket;
    
    TBuffer     TxBuffer;

    TBuffer     RxBuffer;

public:
    TTcpClient(boost::asio::io_context &context)
        : Socket(context)
    { }

    void AsyncConnect(const std::string &addr, uint16_t port);

    void AsyncWrite(const TBuffer &buffer);

    void AsyncRead(size_t min);

    void Close();

private:
    void InternalOnClientConnected(const boost::system::error_code &error);

    void InternalOnRead(const boost::system::error_code &error, size_t size);

    void InternalOnWritten(const boost::system::error_code &error, size_t size);
};


}   // namespace NEvenFound::NNetwork 
