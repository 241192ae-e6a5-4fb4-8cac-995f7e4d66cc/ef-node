#include <evenfound/network/session.hpp>

#include <iostream>

namespace NEvenFound::NNetwork {


//--------------------------------------------------------------------------------------------------------------------
void TSession::AsyncWrite(const TBuffer &buffer) {
    TxBuffer = buffer;

    Socket.async_write_some(boost::asio::buffer(TxBuffer.Data(), TxBuffer.Size()), std::bind(
        &TSession::InternalOnWritten, shared_from_this(),
        std::placeholders::_1,
        std::placeholders::_2
    ));
}

//--------------------------------------------------------------------------------------------------------------------
void TSession::AsyncRead(size_t min) {
    RxBuffer.Resize(min);
    Socket.async_read_some(boost::asio::buffer(RxBuffer.Data(), RxBuffer.Size()), std::bind(
        &TSession::InternalOnRead, shared_from_this(),
        std::placeholders::_1,
        std::placeholders::_2
    ));
}

//--------------------------------------------------------------------------------------------------------------------
void TSession::Close() {
    Socket.close();
}


//--------------------------------------------------------------------------------------------------------------------
void TSession::InternalOnRead(const boost::system::error_code &error, size_t size) {
    if (error) {
        OnError(error);
        return;
    }

    RxBuffer.Resize(size);

    OnRead(RxBuffer);
}


//--------------------------------------------------------------------------------------------------------------------
void TSession::InternalOnWritten(const boost::system::error_code &error, size_t size) {
    if (error) {
        OnError(error);
        return;
    }

    OnWritten(size);
}


}   // namespace NEvenFound::NNetwork
