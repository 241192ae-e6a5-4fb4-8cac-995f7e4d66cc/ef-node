
#include <evenfound/serialization.hpp>
#include <evenfound/crypto/signature.hpp>
#include <evenfound/crypto/algorithm.hpp>
#include <evenfound/network/node.hpp>


namespace NEvenFound {


//--------------------------------------------------------------------------------------------------------------------
void TNodeSessionBase::OnAccepted() {
    AsyncRead(16384);
}


//--------------------------------------------------------------------------------------------------------------------
void TNodeSessionBase::OnRead(const TBuffer &buffer) {
    size_t SignatureSize = 0;

    NSerialization::TTypeSerializer<size_t>::Load(buffer.Data(), 0, SignatureSize);
    if (SignatureSize > buffer.Size() - sizeof(size_t)) {
        OnBadMessage();
        return;
    }

    TSignature<TCrc64HashAlgorithm> Signature;
    NSerialization::Load(buffer, Signature);

    const size_t PayloadSize = buffer.Size() - SignatureSize + sizeof(size_t);

    if (!Signature.Verify(buffer.Data() + SignatureSize + sizeof(size_t), PayloadSize, PublicKey)) {
        OnBadMessage();
        return;
    }

    TBuffer MessageBuffer(buffer.Data() + SignatureSize + sizeof(size_t), buffer.Data() + buffer.Size());

    IMessagePtr Message = TMessageFactory::Instance().CreateMessage(MessageBuffer);
    if (!Message) {
        OnBadMessage();
        return;
    }

    OnVerifiedMessage(Message);
}


//--------------------------------------------------------------------------------------------------------------------
void TNodeSessionBase::OnWritten(size_t size) {
    ((void)size);
}


//--------------------------------------------------------------------------------------------------------------------
void TNodeSessionBase::OnError(const boost::system::error_code &error) {
    ((void)error);
}


//--------------------------------------------------------------------------------------------------------------------
void TNodeSessionBase::OnClosed() {

}


//--------------------------------------------------------------------------------------------------------------------
void TNodeSessionBase::SendMessage(const TBuffer& buffer) {
    ((void)buffer);
}

}   // namespace TEvenFound
