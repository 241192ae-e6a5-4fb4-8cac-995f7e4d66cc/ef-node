#pragma once

#include <evenfound/buffer.hpp>
#include <evenfound/crypto/rsa.hpp>


namespace NEvenFound {

/**
 *
 */
class TSignatureBase {
    TBuffer Value;

protected:
    void Sign(const TBigInteger &hash, const TRsaPrivateKey& key);

    bool Verify(const TBigInteger &hash, const TRsaPublicKey& key) const;

    const TBuffer& Signature() const {
        return Value;
    }

    std::string String() const;
};


/**
 *
 */
template <class THashAlgorithm>
class TSignature : public TSignatureBase {
public:
    /**
     *
     */
    void Sign(const TBuffer& data, const TRsaPrivateKey& key) {
        const TBigInteger hash = THashAlgorithm::Calculate(data);
        TSignatureBase::Sign(hash, key);
    }

    /**
     *
     */
    bool Verify(const TBuffer& data, const TRsaPublicKey& key) const {
        const TBigInteger hash = THashAlgorithm::Calculate(data);
        return TSignatureBase::Verify(hash, key);
    }
};

}   // namespace NEvenFound
