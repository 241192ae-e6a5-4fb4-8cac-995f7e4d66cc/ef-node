#include <gtest/gtest.h>
#include <evenfound/message/message_handler.hpp>
#include <evenfound/message/ping.hpp>


TEST(TMessageHandler, StoreCreateAndHandle) {
    struct THandler : public NEvenFound::TMessageHandler<THandler, NEvenFound::NMessage::TPingMsg> {
        uint64_t MessageType { 0 };
        void OnMessage(const NEvenFound::NMessage::TPingMsg &message) {
            MessageType = message.GetMessageId();    
        }
    };

    NEvenFound::IMessagePtr OriginalMessage = NEvenFound::MakeMessage<NEvenFound::NMessage::TPingMsg>("Hello world!");
    NEvenFound::TBuffer Buffer;
    NEvenFound::TMessageFactory& Factory = NEvenFound::TMessageFactory::Instance();

    OriginalMessage->Store(Buffer);

    NEvenFound::IMessagePtr RestoredMessage = Factory.CreateMessage(Buffer);

    THandler Handler;
    Handler.HandleMessage(RestoredMessage);

    EXPECT_EQ(Handler.MessageType, NEvenFound::NMessage::TPingMsg::CMessageType);
}
