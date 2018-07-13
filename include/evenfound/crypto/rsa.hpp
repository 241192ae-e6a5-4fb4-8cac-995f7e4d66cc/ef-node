#pragma once

#include <evenfound/math/bigint.hpp>


namespace NEvenFound {


/**
 *  @brief RSA private key
 */
struct TRsaPrivateKey {
    TBigInteger N;  /*!< modulus */

    TBigInteger E;  /*!< public exponent */

    TBigInteger D;  /*!< private exponent */

    TBigInteger P;  /*!< prime 1 */

    TBigInteger Q;  /*!< prime 2 */

    static const TRsaPrivateKey LoadFromFile(const std::string &path) {
        return TRsaPrivateKey(path);
    }

    TRsaPrivateKey() = default;

    TRsaPrivateKey(const TRsaPrivateKey&) = default;

private:
    TRsaPrivateKey(const std::string &path);
};


/**
 *  @brief RSA public key
 */
struct TRsaPublicKey {
    TBigInteger N;  /*!< modulus */

    TBigInteger E;  /*!< public exponent */

    static const TRsaPublicKey LoadFromFile(const std::string &path) {
        return TRsaPublicKey(path);
    }

    TRsaPublicKey() = default;

    TRsaPublicKey(const TRsaPublicKey&) = default;
private:
    TRsaPublicKey(const std::string &path);
};


}   // namespace NEvenFound
