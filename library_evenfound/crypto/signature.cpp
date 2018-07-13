#include <evenfound/crypto/signature.hpp>
#include <iostream>


namespace NEvenFound {

void TSignatureBase::Sign(const TBigInteger &hash, const TRsaPrivateKey& key) {
    TBigInteger SignedHash = PowMod(hash, key.D, key.N);
    std::string Signature = SignedHash.AsString(16);

    NSerialization::Store(Value, Signature);
}


bool TSignatureBase::Verify(const TBigInteger &hash, const TRsaPublicKey& key) const {
    std::string Signature;
    NSerialization::Load(Value, Signature);

    TBigInteger SignedHash(Signature);
    TBigInteger RestoredHash = PowMod(SignedHash, key.E, key.N);

    return hash == RestoredHash;
}

std::string TSignatureBase::String() const {
    return Value.HexString();
}

}   // namespace NEvenFound
