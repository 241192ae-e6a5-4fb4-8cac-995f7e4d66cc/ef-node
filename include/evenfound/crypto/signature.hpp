#pragma once

#include <evenfound/buffer.hpp>
#include <evenfound/crypto/rsa.hpp>
#include <evenfound/serialization.hpp>


namespace NEvenFound {

/**
 *
 */
class TSignatureBase {
    TBuffer Value;

public:
    const TBuffer& Signature() const {
        return Value;
    }

    TBuffer& Signature() {
        return Value;
    }

    std::string String() const;

protected:
    void Sign(const TBigInteger &hash, const TRsaPrivateKey& key);

    bool Verify(const TBigInteger &hash, const TRsaPublicKey& key) const;
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
        const TBigInteger Hash = THashAlgorithm::Calculate(data.Data(), data.Size());
        TSignatureBase::Sign(Hash, key);
    }

    /**
     *
     */
    bool Verify(const TBuffer& data, const TRsaPublicKey& key) const {
        const TBigInteger Hash = THashAlgorithm::Calculate(data.Data(), data.Size());
        return TSignatureBase::Verify(Hash, key);
    }

    /**
     *
     */
    bool Verify(const uint8_t *data, size_t size, const TRsaPublicKey& key) const {
        const TBigInteger Hash = THashAlgorithm::Calculate(data, size);
        return TSignatureBase::Verify(Hash, key);
    }
};


namespace NSerialization {

template <typename THashAlgorithm>
struct TTypeSerializer<TSignature<THashAlgorithm>> {
    /**
     *
     */
    static size_t Store(uint8_t *dest, size_t offset, const TSignature<THashAlgorithm>& src) {
        return TTypeSerializer<TBuffer>::Store(dest, offset, src.Signature());
    }

    /**
     *
     */
    static size_t Load(const uint8_t *src, size_t offset, TSignature<THashAlgorithm>& dest) {
        return TTypeSerializer<TBuffer>::Load(src, offset, dest.Signature());
    }
};

}   // namespace NSerialization

}   // namespace NEvenFound


