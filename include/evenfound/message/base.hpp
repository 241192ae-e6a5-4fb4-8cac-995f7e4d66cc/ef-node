#pragma once

#include <memory>
#include <map>
#include <atomic>
#include <utility>

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

template <class TMessage, typename ... Args>
IMessagePtr MakeMessage(Args&& ...);


/**
 *
 */
struct IMessageFactory {
    virtual ~IMessageFactory() { }

    virtual IMessagePtr CreateMessage(const TBuffer &buffer) const = 0;
};

using IMessageFactoryPtr = std::shared_ptr<IMessageFactory>;


/**
 *
 */
template <class TMessage>
struct TSimpleMessageFactory 
    : public IMessageFactory 
{
    IMessagePtr CreateMessage(const TBuffer &buffer) const {
        IMessagePtr Message = MakeMessage<TMessage>();

        Message->Load(buffer);
        return Message;
    }
};


/**
 *
 */
class TMessageFactory 
    : public IMessageFactory 
{
    std::map<uint64_t, IMessageFactoryPtr> MessageFactories;

    TMessageFactory();

public:
    IMessagePtr CreateMessage(const TBuffer &buffer) const;

    template <class TMessage>
    void RegisterMessage() {
        MessageFactories[TMessage::CMessageType] = std::make_shared<TSimpleMessageFactory<TMessage>>();
    }

    static TMessageFactory& Instance() {
        static TMessageFactory Factory;
        return Factory;
    }
};




template <class TMessage> struct TMessageInitializer;


template <class TMessage>
struct TMessageBase 
    : public IMessage
{
    uint64_t MessageId { TMessage::CMessageType };

    TMessageBase() { }

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


template <class TMessage> 
struct TMessageInitializer {
    std::atomic_bool OnceFlag { true };

    TMessageInitializer() {
        if (OnceFlag.exchange(false)) {
            TMessageFactory::Instance().RegisterMessage<TMessage>();        
        }
    }
};


#define EF_REGISTER_MESSAGE(klass) \
static TMessageInitializer<klass> __MessageInitializer_ ## klass;



#define EF_MESSAGE_META(name) \
static constexpr uint64_t CMessageType = NMeta::CRC64(name); \
static constexpr const char* CMessageName = name;


template <class TMessage, typename ... Args>
IMessagePtr MakeMessage(Args&& ...args) {
    return std::make_shared<TMessage>(std::forward<Args>(args)...);
}


}   // namespace NEvenFound
