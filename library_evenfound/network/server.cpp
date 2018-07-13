#include <evenfound/network/server.hpp>

namespace NEvenFound::NNetwork {


//--------------------------------------------------------------------------------------------------------------------
TTcpServer::TTcpServer(ISessionFactoryPtr factory)
    : SessionFactory(factory)
{
}


//--------------------------------------------------------------------------------------------------------------------
TTcpServer::TTcpServer(ISessionFactoryPtr factory, ITcpServerCallbackPtr callback)
    : SessionFactory(factory)
    , Callback(callback)
{ }


//--------------------------------------------------------------------------------------------------------------------
void TTcpServer::Run(uint16_t port) {
    //
    //  configure singal handling
    //
    SignalSet.add(SIGINT);
    SignalSet.async_wait(std::bind(&TTcpServer::OnSignal, this, std::placeholders::_1, std::placeholders::_2));

    //
    //  configure acceptor
    //
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    Acceptor.open(endpoint.protocol());
    Acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    Acceptor.bind(endpoint);
    Acceptor.listen();

    StartAccept();

    Callback->OnStarted(shared_from_this());

    Context.run();

    Callback->OnStopped(shared_from_this());
}


//--------------------------------------------------------------------------------------------------------------------
void TTcpServer::Stop() {
    Acceptor.cancel();
    Context.stop();
}


//--------------------------------------------------------------------------------------------------------------------
void TTcpServer::StartAccept() {
    Acceptor.async_accept(Socket, std::bind(&TTcpServer::OnAccepted, this));
}


//--------------------------------------------------------------------------------------------------------------------
void TTcpServer::OnAccepted() {
    ISessionPtr Session = SessionFactory->CreateSession(Socket);
    Session->OnAccepted();
    StartAccept();
}


//--------------------------------------------------------------------------------------------------------------------
void TTcpServer::OnSignal(const boost::system::error_code&, int signum) {
    switch (signum) {
        case SIGTERM:
        case SIGINT:
            Stop();
            break;
    }
}


}   // namespace NEvenFound::NNetwork
