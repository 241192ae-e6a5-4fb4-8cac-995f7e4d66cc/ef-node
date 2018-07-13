#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <gmp.h>

#include <evenfound/buffer.hpp>


namespace NEvenFound {


struct TStdFreeDeleter {
    void operator()(void *ptr) {
        std::free(ptr);
    }
};


/**
 *  @brief libgmp-based implementation of big integer
 */
class TBigInteger {
    mpz_t Value;

public:
    TBigInteger() {
        mpz_init(Value);
    }

    explicit TBigInteger(uint64_t value) {
        mpz_init_set_ui(Value, value);
    }

    explicit TBigInteger(const char *value, int base=0) {
        base = !base ? GuessBase(value) : base;
        mpz_init_set_str(Value, value, base);
    }

    TBigInteger(const std::string& value, int base=0) {
        base = !base ? GuessBase(value.c_str()) : base;
        mpz_init_set_str(Value, value.c_str(), base);
    }

    TBigInteger(mpz_t value) {
        mpz_init_set(Value, value);
    }

    TBigInteger(const TBigInteger& other) {
        mpz_init_set(Value, other.Value);
    }

    TBigInteger(const TBuffer& buffer) {
        const std::string value = buffer.HexString();
        mpz_init_set_str(Value, value.c_str(), 16);
    }

    TBigInteger(TBigInteger&& other) {
        Value[0] = other.Value[0];
        other.Value->_mp_alloc = 0;
        other.Value->_mp_d = nullptr;
        other.Value->_mp_size = 0;
    }

    TBigInteger& operator=(const TBigInteger& other) {
        mpz_set(Value, other.Value);
        return *this;
    }

    TBigInteger& operator=(TBigInteger&& other) {
        Value[0] = other.Value[0];
        other.Value->_mp_alloc = 0;
        other.Value->_mp_d = nullptr;
        other.Value->_mp_size = 0;
        return *this;
    }

    ~TBigInteger() {
        mpz_clear(Value);
    }

    uint64_t AsInt() const {
        return mpz_get_ui(Value);
    }

    std::string AsString(int base = 10) const {
        std::unique_ptr<char, TStdFreeDeleter> r(mpz_get_str(nullptr, base, Value));
        return std::string(r.get());
    }

    TBigInteger operator+(const TBigInteger& rhs) const {
        TBigInteger result;
        mpz_add(result.Value, Value, rhs.Value);
        return result;
    }

    TBigInteger operator+(uint64_t rhs) const {
        TBigInteger result;
        mpz_add_ui(result.Value, Value, rhs);
        return result;
    }

    TBigInteger operator+(const std::string& rhs) const {
        TBigInteger other(rhs);
        return *this + other;
    }

    TBigInteger operator-(const TBigInteger& rhs) const {
        TBigInteger result;
        mpz_sub(result.Value, Value, rhs.Value);
        return result;
    }

    TBigInteger operator-(uint64_t rhs) const {
        TBigInteger result;
        mpz_sub_ui(result.Value, Value, rhs);
        return result;
    }

    TBigInteger operator-(const std::string& rhs) const {
        TBigInteger other(rhs);
        return *this - other;
    }

    TBigInteger operator*(const TBigInteger& rhs) const {
        TBigInteger result;
        mpz_mul(result.Value, Value, rhs.Value);
        return result;
    }

    TBigInteger operator*(uint64_t rhs) const {
        TBigInteger result;
        mpz_mul_ui(result.Value, Value, rhs);
        return result;
    }

    TBigInteger operator*(const std::string& rhs) const {
        TBigInteger other(rhs);
        return *this * other;
    }

    TBigInteger operator/(const TBigInteger& rhs) const {
        TBigInteger result;
        mpz_div(result.Value, Value, rhs.Value);
        return result;
    }

    TBigInteger operator/(uint64_t rhs) const {
        TBigInteger result;
        mpz_div_ui(result.Value, Value, rhs);
        return result;
    }

    TBigInteger operator/(const std::string& rhs) const {
        TBigInteger other(rhs);
        return *this / other;
    }

    /**
     *
     */
    bool operator==(const TBigInteger& other) const {
        return !mpz_cmp(Value, other.Value);
    }

    bool operator==(uint64_t other) const {
        return !mpz_cmp_ui(Value, other);
    }

    /**
     *
     */
    bool operator!=(const TBigInteger& other) const {
        return mpz_cmp(Value, other.Value);
    }

    bool operator!=(uint64_t other) const {
        return mpz_cmp_ui(Value, other);
    }

    /**
     *
     */
    bool operator<(const TBigInteger& other) const {
        return mpz_cmp(Value, other.Value) < 0;
    }

    bool operator<(uint64_t other) const {
        return mpz_cmp_ui(Value, other) < 0;
    }

    /**
     *
     */
    bool operator>(const TBigInteger& other) const {
        return mpz_cmp(Value, other.Value) > 0;
    }

    bool operator>(uint64_t other) const {
        return mpz_cmp_ui(Value, other) > 0;
    }

    /**
     *
     */
    bool operator<=(const TBigInteger& other) const {
        return operator<(other) || operator==(other);
    }

    bool operator<=(uint64_t other) const {
        return operator<(other) || operator==(other);
    }

    /**
     *
     */
    bool operator>=(const TBigInteger& other) const {
        return operator>(other) || operator==(other);
    }

    bool operator>=(uint64_t other) const {
        return operator>(other) || operator==(other);
    }


    /**
     *  @brief guess base of the integer
     */
    static int GuessBase(const char *value) {
        const char *p = value;
        int base = 0;
        while (p && *p != 0) {
            if (std::isdigit(*p)) {
                const int value = *p - 0x2F;
                base = value > base ? value : base;
            } else if (std::isalpha(*p)) {
                const int value = std::isupper(*p) ? *p - 'A' + 11 : *p - 'a' + 11;
                base = value > base ? value : base;
            }
            ++p;
        }

        for (int r : { 10, 16, 32, 64 }) {
            if (base <= r) {
                return r;
            }
        }

        return 0;   // throw exception ?
    }


    /**
     *  @brief 
     */
    static inline TBigInteger PowMod(const TBigInteger& base, const TBigInteger& exp, const TBigInteger& mod) {
        TBigInteger result;
        mpz_powm(result.Value, base.Value, exp.Value, mod.Value);
        return result;
    }
};  // class TBigInteger


//--------------------------------------------------------------------------------------------------------------------
static inline TBigInteger PowMod(const TBigInteger& base, const TBigInteger& exp, const TBigInteger& mod) {
    return TBigInteger::PowMod(base, exp, mod);
}


}   // namespace NEvenFound
