#include <evenfound/crypto/signature.hpp>
#include <iostream>


namespace NEvenFound {

void TSignatureBase::Sign(const TBigInteger &hash, const TRsaPrivateKey& key) {
    TBigInteger SignedHash = PowMod(hash, key.D, key.N);
    std::string Signature = SignedHash.AsString(16);

    //std::cerr << "SIGN HASH      " << hash.AsString(16) << std::endl;
    //std::cerr << "SIGN SIGNATURE " << Signature << std::endl;

    NSerialization::Store(Value, Signature);
}


bool TSignatureBase::Verify(const TBigInteger &hash, const TRsaPublicKey& key) const {
    std::string Signature;

    NSerialization::Load(Value, Signature);

    //std::cerr << "VERIFY SIGNATURE " << Signature << std::endl;

    TBigInteger SignedHash(Signature, 16);
    TBigInteger RestoredHash = PowMod(SignedHash, key.E, key.N);

    //std::cerr << "VERIFY RESTORED   HASH " << RestoredHash.AsString(16) << std::endl;
    //std::cerr << "VERIFY CALCULATED HASH " << hash.AsString(16) << std::endl;

    return hash == RestoredHash;
}

std::string TSignatureBase::String() const {
    return Value.HexString();
}

}   // namespace NEvenFound
