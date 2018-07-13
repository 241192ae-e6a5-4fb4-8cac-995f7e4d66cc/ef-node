#include <evenfound/crypto/rsa.hpp>
#include <evenfound/crypto/exception.hpp>
#include <evenfound/crypto/asn1.hpp>

#include <evenfound/helpers/read_file.hpp>


namespace NEvenFound {

//--------------------------------------------------------------------------------------------------------------------
struct TParserCallbackBase : public IAsnParserCallback {
    int Counter { 0 };

    void OnSequenceBegin(int, size_t) { }

    void OnSequenceEnd(int) { }
};


//--------------------------------------------------------------------------------------------------------------------
TRsaPrivateKey::TRsaPrivateKey(const std::string &path) {
    struct TCallback : public TParserCallbackBase {
        TRsaPrivateKey& Key;

        TCallback(TRsaPrivateKey& key) : Key(key) { }

        void OnInteger(TBigInteger value) {
            switch (Counter) {
                case 1: Key.N = value; break;
                case 2: Key.E = value; break;
                case 3: Key.D = value; break;
                case 4: Key.P = value; break;
                case 5: Key.Q = value; break;
            }
            Counter++;
        }
    } callback(*this);

    TBuffer content;
    NHelpers::ReadFile(path, content);
    Asn1Parse(content, &callback);
}


//--------------------------------------------------------------------------------------------------------------------
TRsaPublicKey::TRsaPublicKey(const std::string &path) {
    struct TCallback : public TParserCallbackBase {
        TRsaPublicKey& Key;

        TCallback(TRsaPublicKey& key) : Key(key) { }

        void OnInteger(TBigInteger value) {
            switch (Counter) {
                case 0: Key.N = value; break;
                case 1: Key.E = value; break;
            }
            Counter++;
        }
    } callback(*this);

    TBuffer content;
    NHelpers::ReadFile(path, content);
    Asn1Parse(content, &callback);
}


}   // namespace NEvenFound
