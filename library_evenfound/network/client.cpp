#include <evenfound/network/client.hpp>

namespace NEvenFound::NNetwork {


void TTcpClient::AsyncConnect(const std::string &addr, uint16_t port) {
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::make_address(addr), port);
    Socket.async_connect(ep, std::bind(
        &TTcpClient::InternalOnClientConnected,
        shared_from_this(),
        std::placeholders::_1
    ));
}

void TTcpClient::AsyncWrite(const TBuffer &buffer) {
    Socket.async_write_some(
        boost::asio::buffer(buffer.Data(), buffer.Size()),
        std::bind(
            &TTcpClient::InternalOnWritten,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2
    ));
}

void TTcpClient::AsyncRead(size_t min) {
    RxBuffer.Resize(min);
    Socket.async_read_some(
        boost::asio::buffer(RxBuffer.Data(), RxBuffer.Size()),
        std::bind(
            &TTcpClient::InternalOnRead,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2
    ));
}

void TTcpClient::Close() {
    Socket.close();
    OnClientClosed();
}


void TTcpClient::InternalOnClientConnected(const boost::system::error_code &error) {
    if (error) {
        OnClientError(error);
        return;
    }

    OnClientConnected();
}


void TTcpClient::InternalOnRead(const boost::system::error_code &error, size_t size) {
    if (error) {
        OnClientError(error);
        Close();
        return;
    }

    RxBuffer.Resize(size);
    OnClientRead(RxBuffer);
}


void TTcpClient::InternalOnWritten(const boost::system::error_code &error, size_t size) {
    if (error) {
        OnClientError(error);
        Close();
        return;
    }

    OnClientWritten(size);
}

}   // namespace NEvenFound::NNetwork 
