#include <gtest/gtest.h>

#include <evenfound/crypto/asn1.hpp>

/*
    0:d=0  hl=2 l=  43 cons: SEQUENCE          
    2:d=1  hl=2 l=   1 prim: INTEGER           :00
    5:d=1  hl=2 l=   5 prim: INTEGER           :D5A87A65
   12:d=1  hl=2 l=   3 prim: INTEGER           :010001
   17:d=1  hl=2 l=   4 prim: INTEGER           :07E6FA01
   23:d=1  hl=2 l=   3 prim: INTEGER           :FFF1
   28:d=1  hl=2 l=   3 prim: INTEGER           :D5B5
   33:d=1  hl=2 l=   2 prim: INTEGER           :7871
   37:d=1  hl=2 l=   2 prim: INTEGER           :4F55
   41:d=1  hl=2 l=   2 prim: INTEGER           :5B7E
*/

const NEvenFound::TBuffer SampleRsaKey {
    0x30, 0x2b, 0x02, 0x01, 0x00, 0x02, 0x05, 0x00,
    0xd5, 0xa8, 0x7a, 0x65, 0x02, 0x03, 0x01, 0x00,
    0x01, 0x02, 0x04, 0x07, 0xe6, 0xfa, 0x01, 0x02,
    0x03, 0x00, 0xff, 0xf1, 0x02, 0x03, 0x00, 0xd5,
    0xb5, 0x02, 0x02, 0x78, 0x71, 0x02, 0x02, 0x4f,
    0x55, 0x02, 0x02, 0x5b, 0x7e
};


struct TAsnParserCallback : public NEvenFound::IAsnParserCallback {
    std::vector<NEvenFound::TBigInteger> Values;
    int MaxLevel { 0 };
    size_t MaxSize { 0 };

    void OnSequenceBegin(int level, size_t size) { 
        if (level > MaxLevel) {
            MaxLevel = level;
        }

        if (size > MaxSize) {
            MaxSize = size;
        }
    }

    void OnSequenceEnd(int) { }

    void OnInteger(NEvenFound::TBigInteger value) {
        Values.push_back(value);
    }
};

TEST(Asn1Parser, ParseEmptySequence) {
    const NEvenFound::TBuffer EmptySequence { 0x30, 0x00 };
    TAsnParserCallback callback;    
    NEvenFound::Asn1Parse(EmptySequence, &callback);

    EXPECT_EQ(callback.MaxLevel, 0);
    EXPECT_EQ(callback.MaxSize, 0);
}

TEST(Asn1Parser, ParseEmptySequenceWithLongSize) {
    const NEvenFound::TBuffer EmptySequence { 0x30, 0x81, 0x00 };
    TAsnParserCallback callback;    
    NEvenFound::Asn1Parse(EmptySequence, &callback);

    EXPECT_EQ(callback.MaxLevel, 0);
    EXPECT_EQ(callback.MaxSize, 0);
}


TEST(Asn1Parser, ParseEmptySequenceWithVeryLongSize) {
    const NEvenFound::TBuffer EmptySequence { 0x30, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    TAsnParserCallback callback;    
    NEvenFound::Asn1Parse(EmptySequence, &callback);

    EXPECT_EQ(callback.MaxLevel, 0);
    EXPECT_EQ(callback.MaxSize, 0);
}


TEST(Asn1Parser, ParseNestedSequence) {
    const NEvenFound::TBuffer EmptySequence { 0x30, 0x02, 0x30, 0x00 };
    TAsnParserCallback callback;    
    NEvenFound::Asn1Parse(EmptySequence, &callback);

    EXPECT_EQ(callback.MaxLevel, 1);
    EXPECT_EQ(callback.MaxSize, 2);
}

TEST(Asn1Parser, ParseOneInteger) {
    const NEvenFound::TBuffer EmptySequence { 0x30, 0x06, 0x02, 0x04, 0xBA, 0xAD, 0xF0, 0x0D };
    TAsnParserCallback callback;    
    NEvenFound::Asn1Parse(EmptySequence, &callback);

    EXPECT_EQ(callback.MaxLevel, 0);
    EXPECT_EQ(callback.MaxSize, 6);
    ASSERT_EQ(callback.Values.size(), 1);
    EXPECT_EQ(callback.Values[0].AsInt(), 0xBAADF00D);
    EXPECT_EQ(callback.Values[0].AsString(16), "baadf00d");
}

TEST(Asn1Parser, ParseOneIntegerWithLongSize) {
    const NEvenFound::TBuffer EmptySequence { 0x30, 0x06, 0x02, 0x81, 0x04, 0xBA, 0xAD, 0xF0, 0x0D };
    TAsnParserCallback callback;    
    NEvenFound::Asn1Parse(EmptySequence, &callback);

    EXPECT_EQ(callback.MaxLevel, 0);
    EXPECT_EQ(callback.MaxSize, 6);
    ASSERT_EQ(callback.Values.size(), 1);
    EXPECT_EQ(callback.Values[0].AsInt(), 0xBAADF00D);
    EXPECT_EQ(callback.Values[0].AsString(16), "baadf00d");
}


TEST(Asn1Parser, ParseRsaKey) {
    TAsnParserCallback callback;    
    NEvenFound::Asn1Parse(SampleRsaKey, &callback);

    EXPECT_EQ(9, callback.Values.size());

    EXPECT_EQ(callback.Values[0].AsInt(), 0x00);
    EXPECT_EQ(callback.Values[1].AsInt(), 0xD5A87A65);
    EXPECT_EQ(callback.Values[2].AsInt(), 0x010001);
    EXPECT_EQ(callback.Values[3].AsInt(), 0x07E6FA01);
    EXPECT_EQ(callback.Values[4].AsInt(), 0xFFF1);
    EXPECT_EQ(callback.Values[5].AsInt(), 0xD5B5);
    EXPECT_EQ(callback.Values[6].AsInt(), 0x7871);
    EXPECT_EQ(callback.Values[7].AsInt(), 0x4F55);
    EXPECT_EQ(callback.Values[8].AsInt(), 0x5B7E);
}


