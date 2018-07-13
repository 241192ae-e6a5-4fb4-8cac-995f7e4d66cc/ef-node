#include <gtest/gtest.h>
#include <evenfound/message/message_handler.hpp>
#include <evenfound/message/ping.hpp>
#include <evenfound/message/pong.hpp>
#include <evenfound/message/text.hpp>


TEST(TMessageHandler, OneKnownMessage) {
    struct THandler : public NEvenFound::TMessageHandler<THandler, NEvenFound::NMessage::TPingMsg> {
        uint64_t MessageType { 0 };
        void OnMessage(const NEvenFound::NMessage::TPingMsg &message) {
            MessageType = message.GetMessageId();    
        }
    };

    NEvenFound::IMessagePtr Message = NEvenFound::MakeMessage<NEvenFound::NMessage::TPingMsg>("Hello world!");
    ASSERT_TRUE(Message);

    THandler Handler;
    Handler.HandleMessage(Message);

    EXPECT_EQ(Handler.MessageType, NEvenFound::NMessage::TPingMsg::CMessageType);
}


TEST(TMessageHandler, Unexpected) {
    struct THandler : public NEvenFound::TMessageHandler<THandler, NEvenFound::NMessage::TPingMsg> {
        uint64_t MessageType { 0 };
        uint64_t UnexpectedCount { 0 };

        void OnMessage(const NEvenFound::NMessage::TPingMsg &message) {
            MessageType = message.GetMessageId();    
        }

        bool OnUnknownMessage(NEvenFound::IMessagePtr) {
            UnexpectedCount += 1;
            return false;
        }
    };

    std::vector<NEvenFound::IMessagePtr> Messages {
        NEvenFound::MakeMessage<NEvenFound::NMessage::TPingMsg>("Hello world!"),
        NEvenFound::MakeMessage<NEvenFound::NMessage::TPongMsg>("Hello world!"),
        NEvenFound::MakeMessage<NEvenFound::NMessage::TTextMsg>("Hello world!"),
    };

    THandler Handler;

    for (const NEvenFound::IMessagePtr &Message : Messages) {
        Handler.HandleMessage(Message);
    }

    EXPECT_EQ(Handler.MessageType, NEvenFound::NMessage::TPingMsg::CMessageType);
    EXPECT_EQ(Handler.UnexpectedCount, 2);
}

TEST(TMessageHandler, TwoKnownMessages) {
    struct THandler 
        : public NEvenFound::TMessageHandler<
            THandler,
            NEvenFound::NMessage::TPingMsg,
            NEvenFound::NMessage::TPongMsg>
    {
        uint64_t MessageType { 0 };
        uint64_t UnexpectedCount { 0 };

        void OnMessage(const NEvenFound::NMessage::TPingMsg &message) {
            MessageType = message.GetMessageId();    
        }

        void OnMessage(const NEvenFound::NMessage::TPongMsg &message) {
            MessageType = message.GetMessageId();    
        }

        bool OnUnknownMessage(NEvenFound::IMessagePtr) {
            UnexpectedCount += 1;
            return false;
        }
    };

    std::vector<NEvenFound::IMessagePtr> Messages {
        NEvenFound::MakeMessage<NEvenFound::NMessage::TPingMsg>("Hello world!"),
        NEvenFound::MakeMessage<NEvenFound::NMessage::TPongMsg>("Hello world!"),
        NEvenFound::MakeMessage<NEvenFound::NMessage::TTextMsg>("Hello world!"),
    };

    THandler Handler;

    for (const NEvenFound::IMessagePtr &Message : Messages) {
        Handler.HandleMessage(Message);
    }

    EXPECT_EQ(Handler.MessageType, NEvenFound::NMessage::TPongMsg::CMessageType);
    EXPECT_EQ(Handler.UnexpectedCount, 1);
}

TEST(TMessageHandler, Null) {
    struct THandler : public NEvenFound::TMessageHandler<THandler, NEvenFound::NMessage::TPingMsg> {
        uint64_t NullCount { 0 };

        void OnMessage(const NEvenFound::NMessage::TPingMsg&) { }

        bool OnNullMessage() {
            NullCount += 1;
            return false;
        }
    };

    THandler Handler;
    Handler.HandleMessage(nullptr);
    EXPECT_EQ(Handler.NullCount, 1);
}
