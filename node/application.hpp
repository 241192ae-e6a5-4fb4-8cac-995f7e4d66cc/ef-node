#pragma once

#include <evenfound/network/server.hpp>
#include <evenfound/network/node.hpp>
#include <evenfound/crypto/rsa.hpp>

#include "settings.hpp"
#include "session.hpp"


class TNodeApplication
    : public NEvenFound::NNetwork::ITcpServerCallback
    , public NEvenFound::NNetwork::ISessionFactory
    , public NEvenFound::INodeClientCallback
    , public std::enable_shared_from_this<TNodeApplication>
{
    NEvenFound::TRsaPrivateKey      MyPrivateKey;

    NEvenFound::TRsaPublicKey       OtherPublicKey;

    std::shared_ptr<NEvenFound::TNodeClient>    NodeClient;

public:
    TNodeSettings   Settings;    

    TNodeApplication(int argc, char **argv)
        : Settings(argc, argv)
    { }


    NEvenFound::NNetwork::ISessionPtr CreateSession(boost::asio::ip::tcp::socket &socket) {
        std::shared_ptr<TNodeSession> Session = std::make_shared<TNodeSession>(socket); 

        Session->SetRsaPublicKey(OtherPublicKey);

        Session->SetRsaPrivateKey(MyPrivateKey);

        return Session;
    }


    void OnStarted(NEvenFound::NNetwork::ITcpServerPtr server) {
        std::clog << "NODE STARTED" << std::endl;

        try {
            std::clog << "NODE LOAD PRIVATE KEY FROM " << Settings.MyPrivateKeyPath << std::endl;
            MyPrivateKey = NEvenFound::TRsaPrivateKey::LoadFromFile(Settings.MyPrivateKeyPath);

            std::clog << "NODE LOAD PUBLIC KEY FROM " << Settings.OtherPublicKeyPath << std::endl;
            OtherPublicKey = NEvenFound::TRsaPublicKey::LoadFromFile(Settings.OtherPublicKeyPath);
        } catch (const std::exception &err) {
            std::cerr << "NODE ERROR " << err.what() << std::endl;
            server->Stop();
        }

        //
        //  Create connection to remote node
        //
        NodeClient = std::make_shared<NEvenFound::TNodeClient>(server->GetContext());
        NodeClient->SetRsaPrivateKey(MyPrivateKey);
        NodeClient->SetRsaPublicKey(OtherPublicKey);
        NodeClient->SetCallback(shared_from_this());
        NodeClient->AsyncConnect(Settings.RemoteAddress, Settings.RemotePort);
    }


    void OnStopped(NEvenFound::NNetwork::ITcpServerPtr) {
        std::cout << "NODE STOPPED" << std::endl;
    }

    void OnNodeConnected() {
        std::cout << "NODE CONNECTED" << std::endl;
        NodeClient->SendMessage<NEvenFound::NMessage::TTextMsg>("Hello world!");
    }

    void OnNodeConnectionError() {
        std::cout << "NODE CONNECTION ERROR" << std::endl;
    }

    void OnNodeDisconnected() {
        std::cout << "NODE DISCONNECTED" << std::endl;
    }

    uint64_t SentMessages { 0 };

    void OnNodeMessageSent() {
        std::cout << "NODE MESSAGE SENT" << std::endl;

        SentMessages += 1;
        if (SentMessages == 10) {
            NodeClient->SendMessage<NEvenFound::NMessage::TShutdownMsg>();
        } else if (SentMessages > 10) {
            NodeClient->Close();
        } else {
            NodeClient->SendMessage<NEvenFound::NMessage::TTextMsg>("ping");
        }
    }

    void OnNodeError() {

    }

    int Run() {
        try {
            auto App = shared_from_this();
            NEvenFound::NNetwork::TTcpServerPtr Server = std::make_shared<NEvenFound::NNetwork::TTcpServer>(App, App);
            Server->Run(Settings.Port);
        } catch (const std::exception& error) {
            return 1;
        }
        return 0;
    }
};
