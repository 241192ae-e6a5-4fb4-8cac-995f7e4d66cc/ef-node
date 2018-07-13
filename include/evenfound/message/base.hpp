#pragma once

#include <memory>

#include <evenfound/meta/crc64.hpp>
#include <evenfound/serialization.hpp>


namespace NEvenFound {

struct IMessage 
    : public NSerialization::ISerializable
{
    virtual ~IMessage() { }

    virtual uint64_t GetMessageId() const = 0;

    virtual const char* GetMessageName() const = 0;
};

using IMessagePtr = std::shared_ptr<IMessage>;


template <class TMessage>
struct TMessageBase 
    : public IMessage
{
    uint64_t MessageId { TMessage::CMessageType };

    uint64_t GetMessageId() const {
        return MessageId;
    }

    const char* GetMessageName() const {
        return TMessage::CMessageName;
    }

    void Store(TBuffer &buffer) const {
        NSerialization::Store(buffer, MessageId);
    }

    void Load(const TBuffer &buffer) {
        NSerialization::Load(buffer, MessageId);
    }
};


#define EF_MESSAGE_META(name) \
static constexpr uint64_t CMessageType = NMeta::CRC64(name); \
static constexpr const char* CMessageName = name;


template <class TMessage, typename ... Args>
IMessagePtr MakeMessage(Args&& ...args) {
    return std::make_shared<TMessage>(std::forward<Args&&...>(args...));
}


}   // namespace NEvenFound
