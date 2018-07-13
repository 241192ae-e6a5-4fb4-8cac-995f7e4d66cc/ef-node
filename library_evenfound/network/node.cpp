#include <evenfound/serialization.hpp>
#include <evenfound/crypto/signature.hpp>
#include <evenfound/crypto/algorithm.hpp>
#include <evenfound/network/node.hpp>

#include <iostream>


namespace NEvenFound {


//--------------------------------------------------------------------------------------------------------------------
void TNodeSessionBase::OnAccepted() {
    AsyncRead(16384);
}


//--------------------------------------------------------------------------------------------------------------------
void TNodeSessionBase::OnRead(const TBuffer &buffer) {
    size_t SignatureSize = 0;

    NSerialization::TTypeSerializer<size_t>::Load(buffer.Data(), 0, SignatureSize);

    //std::cerr << "NODE SESSION READ BUFFER SIZE    " << buffer.Size() << std::endl;
    //std::cerr << "NODE SESSION READ SIGNATURE SIZE " << SignatureSize << std::endl;

    if (buffer.Size() < (SignatureSize + sizeof(size_t))) {
        OnBadMessage();
        return;
    }

    TSignature<TCrc64HashAlgorithm> Signature;
    NSerialization::Load(buffer, Signature);

    //std::cerr << "NODE SESSION READ SIGNATURE BODY " << Signature.String() << std::endl;

    const size_t PayloadSize = buffer.Size() - SignatureSize - sizeof(size_t) * 2;

    //std::cerr << "NODE SESSION READ PAYLOAD SIZE " << PayloadSize << std::endl;

    if (!Signature.Verify(buffer.Data() + SignatureSize + sizeof(size_t) * 2, PayloadSize, PublicKey)) {
        //std::cerr << "NODE SESSION BAD SIGNATURE" << std::endl;
        OnBadMessage();
        AsyncRead(16384);
        return;
    }

    TBuffer MessageBuffer(buffer.Data() + SignatureSize + sizeof(size_t) * 2, buffer.Data() + buffer.Size());

    IMessagePtr Message = TMessageFactory::Instance().CreateMessage(MessageBuffer);
    if (!Message) {
        OnBadMessage();
        AsyncRead(16384);
        return;
    }

    OnVerifiedMessage(Message);
    AsyncRead(16384);
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
    TSignature<TCrc64HashAlgorithm> Signature;
    Signature.Sign(buffer, PrivateKey);

    TBuffer TxBuffer;
    NSerialization::Store(TxBuffer, Signature, buffer);

    AsyncWrite(TxBuffer);
}


//====================================================================================================================
//  TNodeClient
//

void TNodeClient::OnClientConnected() {
    Callback->OnNodeConnected();
}

void TNodeClient::OnClientRead(const TBuffer& buffer) {
    ((void)buffer);
}

void TNodeClient::OnClientWritten(size_t) {
    Callback->OnNodeMessageSent();
}

void TNodeClient::OnClientError(const boost::system::error_code&) {
    if (IsConnected()) {
        Callback->OnNodeError();
    } else {
        Callback->OnNodeConnectionError();
    }
}

void TNodeClient::OnClientClosed() {
    Callback->OnNodeDisconnected();
}

void TNodeClient::SendMessage(const TBuffer& buffer) {
    TSignature<TCrc64HashAlgorithm> Signature;
    Signature.Sign(buffer, PrivateKey);

    TBuffer TxBuffer;
    NSerialization::Store(TxBuffer, Signature, buffer);

    std::cerr << "NODE CLIENT SEND PAYLOAD SIZE         " << buffer.Size() << std::endl;
    //std::cerr << "NODE CLIENT SEND PAYLOAD SIGNATURE    " << Signature.String() << std::endl;
    //std::cerr << "NODE CLIENT SEND BUFFER SIZE          " << TxBuffer.Size() << std::endl;

    AsyncWrite(TxBuffer);
}


}   // namespace TEvenFound
