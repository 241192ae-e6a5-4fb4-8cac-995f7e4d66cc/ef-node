#include <gtest/gtest.h>
#include <iostream>

#include <evenfound/config.hpp>
#include <evenfound/meta/crc64.hpp>


struct TTestResults {
    static constexpr uint64_t Result = NEvenFound::NMeta::CRC64("123456789");
};


template <uint64_t S>
struct TTestChecker {
    static constexpr bool Value = (S == 0xe9c6d914c4b8d9ca);
};


TEST(NMeta, Compile_Time_CRC64) {
    static_assert(TTestChecker<TTestResults::Result>::Value);
    ASSERT_TRUE(TTestChecker<TTestResults::Result>::Value);
}
