#include <evenfound/message/base.hpp>


namespace NEvenFound {

//--------------------------------------------------------------------------------------------------------------------
struct TProbeMessage : public TMessageBase<TProbeMessage>
{
    EF_MESSAGE_META("com.evenfound.TProbeMessage");

    TProbeMessage() { }

    void Store(TBuffer &) const { }

    void Load(const TBuffer &buffer) { 
        NSerialization::Load(buffer, MessageId);
    }
};


//--------------------------------------------------------------------------------------------------------------------
TMessageFactory::TMessageFactory()
{ }


//--------------------------------------------------------------------------------------------------------------------
IMessagePtr TMessageFactory::CreateMessage(const TBuffer &buffer) const {
    TProbeMessage Probe;
    Probe.Load(buffer);

    auto it = MessageFactories.find(Probe.GetMessageId());
    if (it == MessageFactories.end()) {
        return nullptr;
    }

    return it->second->CreateMessage(buffer);
}


}   // namespace NEvenFound
