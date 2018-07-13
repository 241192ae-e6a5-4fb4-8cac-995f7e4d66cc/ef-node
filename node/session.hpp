#pragma once

#include <iostream>
#include <unistd.h>
#include <signal.h>

#include <evenfound/message/ping.hpp>
#include <evenfound/message/pong.hpp>
#include <evenfound/message/text.hpp>
#include <evenfound/message/shutdown.hpp>

#include <evenfound/network/node.hpp>


class TNodeSession;

using TSessionBase = NEvenFound::TNodeSession<TNodeSession,
    NEvenFound::NMessage::TPingMsg,
    NEvenFound::NMessage::TPongMsg,
    NEvenFound::NMessage::TTextMsg,
    NEvenFound::NMessage::TShutdownMsg
>;

class TNodeSession
    : public TSessionBase
{
public:
    using TSessionBase::TSessionBase;

    void OnMessage(const NEvenFound::NMessage::TPingMsg& message) {
        std::cout << "NODE RX PING '" << message.Payload << "'" << std::endl;
    }

    void OnMessage(const NEvenFound::NMessage::TPongMsg& message) {
        std::cout << "NODE RX PONG '" << message.Payload << "'" << std::endl;
    }

    void OnMessage(const NEvenFound::NMessage::TTextMsg& message) {
        std::cout << "NODE RX TEXT '" << message.Payload << "'" << std::endl;
    }

    void OnMessage(const NEvenFound::NMessage::TShutdownMsg&) {
        std::cerr << "NODE SHUTDOWN" << std::endl;
        kill(0, SIGTERM);
    }

    void OnBadMessage() {
        std::cerr << "NODE RX BAD MESSAGE" << std::endl;
    }
};


