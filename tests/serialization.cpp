#include <gtest/gtest.h>
#include <evenfound/serialization.hpp>
#include <evenfound/serialization/string.hpp>
#include <evenfound/serialization/vector.hpp>

#include <evenfound/message/ping.hpp>


namespace NSerialization = NEvenFound::NSerialization;


TEST(Serialization, PrimitiveType) {
    NEvenFound::TBuffer buffer;
    uint64_t OriginalValue0 = 0xDEADBEEFBAADF00D;
    uint64_t OriginalValue1 = 0xDEADBEEFBAADF00D;
    uint64_t RestoredValue0 = 0;
    uint64_t RestoredValue1 = 0;

    NSerialization::Store(buffer, OriginalValue0, OriginalValue1);

    ASSERT_EQ(buffer.Size(), 16);

    NSerialization::Load(buffer, RestoredValue0, RestoredValue1);

    EXPECT_EQ(RestoredValue0, OriginalValue0);
    EXPECT_EQ(RestoredValue1, OriginalValue1);
}


TEST(Serialization, String) {
    NEvenFound::TBuffer buffer;
    std::string OriginalValue0 = "0xDEADBEEFBAADF00D";
    std::string RestoredValue0;

    NSerialization::Store(buffer, OriginalValue0);
    NSerialization::Load(buffer, RestoredValue0);

    EXPECT_EQ(RestoredValue0, OriginalValue0);
}


TEST(Serialization, VectorOfPrimitiveType) {
    NEvenFound::TBuffer buffer;
    std::vector<uint64_t> OriginalValue0 {
        1, 2, 3, 4, 5, 42
    };
    std::vector<uint64_t> RestoredValue0;

    NSerialization::Store(buffer, OriginalValue0);
    NSerialization::Load(buffer, RestoredValue0);

    EXPECT_EQ(RestoredValue0, OriginalValue0);
}

TEST(Serialization, VectorOfStrings) {
    NEvenFound::TBuffer buffer;
    std::vector<std::string> OriginalValue0 {
        std::string("hello world!"),
        std::string("goodbye world!"),
    };
    std::vector<std::string> RestoredValue0;

    NSerialization::Store(buffer, OriginalValue0);
    NSerialization::Load(buffer, RestoredValue0);

    EXPECT_EQ(RestoredValue0, OriginalValue0);
}


TEST(Serialization, Message) {
    NEvenFound::TBuffer buffer;
    NEvenFound::NMessage::TPingMsg OriginalMessage("hello");
    NEvenFound::NMessage::TPingMsg RestoredMessage;
    
    OriginalMessage.Store(buffer);
    RestoredMessage.Load(buffer);

    EXPECT_EQ(RestoredMessage.MessageId, OriginalMessage.MessageId);
    EXPECT_EQ(RestoredMessage.Payload, OriginalMessage.Payload);
}
