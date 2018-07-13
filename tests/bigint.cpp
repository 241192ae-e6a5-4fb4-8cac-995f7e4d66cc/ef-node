#include <gtest/gtest.h>
#include <evenfound/math/bigint.hpp>


//--------------------------------------------------------------------------------------------------------------------
TEST(TBigInteger, GuessBase) {
    EXPECT_EQ(10, NEvenFound::TBigInteger::GuessBase("01010101"));
    EXPECT_EQ(10, NEvenFound::TBigInteger::GuessBase("20"));
    EXPECT_EQ(10, NEvenFound::TBigInteger::GuessBase("03010101"));
    EXPECT_EQ(10, NEvenFound::TBigInteger::GuessBase("07010101"));
    EXPECT_EQ(16, NEvenFound::TBigInteger::GuessBase("0A"));
    EXPECT_EQ(16, NEvenFound::TBigInteger::GuessBase("FF"));
}


//--------------------------------------------------------------------------------------------------------------------
TEST(TBigInteger, BasicOperations) {
    NEvenFound::TBigInteger a("10");
    NEvenFound::TBigInteger b(20);

    EXPECT_EQ(30, (a + b).AsInt());;
    EXPECT_EQ(10, (b - a).AsInt());;
    EXPECT_EQ(200, (a * b).AsInt());;
    EXPECT_EQ(2, (b / a).AsInt());;
}


//--------------------------------------------------------------------------------------------------------------------
TEST(TBigInteger, PowMod) {
    NEvenFound::TBigInteger A(42424);
    NEvenFound::TBigInteger N(47561); // (0xb9c9)
    NEvenFound::TBigInteger E(65537); // (0x10001)
    NEvenFound::TBigInteger D(31085); // (0x796d)

    NEvenFound::TBigInteger R = NEvenFound::PowMod(A, E, N);
    NEvenFound::TBigInteger B = NEvenFound::PowMod(R, D, N);

    EXPECT_EQ(A.AsInt(), B.AsInt());
    EXPECT_EQ(A.AsString(), B.AsString());
}
