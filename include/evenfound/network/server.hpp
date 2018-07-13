#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>

#include <evenfound/network/session.hpp>


namespace NEvenFound::NNetwork {

struct ITcpServer {
    virtual ~ITcpServer() { }

    virtual void Run(uint16_t port) = 0;

    virtual void Stop() = 0;

    virtual boost::asio::io_context& GetContext() = 0;
};

using ITcpServerPtr = std::shared_ptr<ITcpServer>;


/**
 *
 */
struct ITcpServerCallback {
    virtual ~ITcpServerCallback() { }

    virtual void OnStarted(ITcpServerPtr server) = 0;

    virtual void OnStopped(ITcpServerPtr server) = 0;
};

using ITcpServerCallbackPtr = std::shared_ptr<ITcpServerCallback>;


/**
 *
 */
class TTcpServer
    : public ITcpServer
    , public std::enable_shared_from_this<TTcpServer>
{
    boost::asio::io_context         Context;

    boost::asio::ip::tcp::acceptor  Acceptor { Context };

    boost::asio::ip::tcp::socket    Socket { Context };

    boost::asio::signal_set         SignalSet { Context };

    ISessionFactoryPtr              SessionFactory;

    ITcpServerCallbackPtr           Callback;

public:
    TTcpServer(ISessionFactoryPtr factory);

    TTcpServer(ISessionFactoryPtr factory, ITcpServerCallbackPtr callback);

    void Run(uint16_t port);

    void Stop();

    boost::asio::io_context& GetContext() {
        return Context;
    }

private: /* methods */
    void StartAccept();

    void OnAccepted();

    void OnSignal(const boost::system::error_code&, int signum);
};

using TTcpServerPtr = std::shared_ptr<TTcpServer>;


}   // namespace NEvenFound::NNetwork
