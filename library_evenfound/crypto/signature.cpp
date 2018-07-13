#include <evenfound/crypto/signature.hpp>


namespace NEvenFound {

void TSignatureBase::Sign(const TBigInteger &hash, const TRsaPrivateKey& key) {
    (void)hash;
    (void)key;
}

bool TSignatureBase::Verify(const TBigInteger &hash, const TRsaPublicKey& key) const {
    TBigInteger S(Value);

    (void)hash;
    (void)key;

    return false;
}

std::string TSignatureBase::String() const {
    return "";
}

}   // namespace NEvenFound
