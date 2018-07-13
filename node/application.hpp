#pragma once

#include <evenfound/network/server.hpp>
#include <evenfound/crypto/rsa.hpp>

#include "settings.hpp"
#include "session.hpp"


class TNodeApplication
    : public NEvenFound::NNetwork::ITcpServerCallback
    , public NEvenFound::NNetwork::ISessionFactory
{
    NEvenFound::TRsaPrivateKey  MyPrivateKey;

    NEvenFound::TRsaPublicKey   OtherPublicKey;

public:
    TNodeSettings               Settings;    

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
    }


    void OnStopped(NEvenFound::NNetwork::ITcpServerPtr) {
        std::cout << "NODE STOPPED" << std::endl;
    }
};
