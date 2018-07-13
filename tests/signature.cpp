#include <gtest/gtest.h>
#include <evenfound/config.hpp>
#include <evenfound/crypto/signature.hpp>
#include <evenfound/crypto/algorithm.hpp>
#include <evenfound/serialization.hpp>


TEST(Signature, SignAndVerify) {
    NEvenFound::TRsaPrivateKey PrivateKey = NEvenFound::TRsaPrivateKey::LoadFromFile(std::string(NEvenFound::NConfig::CPrivateKeysDir) + "/test.key");
    NEvenFound::TRsaPublicKey PublicKey = NEvenFound::TRsaPublicKey::LoadFromFile(std::string(NEvenFound::NConfig::CPublicKeysDir) + "/test_pub.key");

    ASSERT_EQ(PrivateKey.N.AsString(16), PublicKey.N.AsString(16));
    ASSERT_EQ(PrivateKey.E.AsString(16), PublicKey.E.AsString(16));

    std::string Value = "Hello world";
    NEvenFound::TBuffer Buffer;

    NEvenFound::NSerialization::Store(Buffer, Value);

    NEvenFound::TSignature<NEvenFound::TCrc64HashAlgorithm> Signature;
    Signature.Sign(Buffer, PrivateKey);

    EXPECT_TRUE(Signature.Verify(Buffer, PublicKey));
    Buffer[0] = 'F';

    EXPECT_FALSE(Signature.Verify(Buffer, PublicKey));
}

TEST(Signature, Serialization) {
    NEvenFound::TRsaPrivateKey PrivateKey = NEvenFound::TRsaPrivateKey::LoadFromFile(std::string(NEvenFound::NConfig::CPrivateKeysDir) + "/test.key");
    NEvenFound::TRsaPublicKey PublicKey = NEvenFound::TRsaPublicKey::LoadFromFile(std::string(NEvenFound::NConfig::CPublicKeysDir) + "/test_pub.key");

    ASSERT_EQ(PrivateKey.N.AsString(16), PublicKey.N.AsString(16));
    ASSERT_EQ(PrivateKey.E.AsString(16), PublicKey.E.AsString(16));

    NEvenFound::TBuffer buffer0;
    NEvenFound::TBuffer buffer1;
    NEvenFound::TBuffer buffer2;
    NEvenFound::TBuffer Payload { 0x00, 0x11, 0x22, 0x33 };
    NEvenFound::TSignature<NEvenFound::TCrc64HashAlgorithm> Original;
    NEvenFound::TSignature<NEvenFound::TCrc64HashAlgorithm> Restored;

    Original.Sign(Payload, PrivateKey);
    
    NEvenFound::NSerialization::Store(buffer0, Payload, Original);
    NEvenFound::NSerialization::Load(buffer0, Payload, Restored);

    EXPECT_EQ(Restored.String(), Original.String());
    EXPECT_TRUE(Restored.Verify(Payload, PublicKey));
}

