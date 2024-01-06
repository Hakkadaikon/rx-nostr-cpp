#ifndef NOSTR_EVENT_HPP
#define NOSTR_EVENT_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace rx_nostr
{
using NostrEventId        = std::string;
using NostrEventKind      = uint16_t;
using NostrEventKinds     = std::vector<uint16_t>;
using NostrEventTagItem   = std::string;
using NostrEventTags      = std::vector<std::string>;
using NostrEventSignature = std::string;
using NostrEventContent   = std::string;

class NostrEvent final
{
   public:
    NostrEvent(
        const NostrEventId&        id,
        const NostrEventKind&      kind,
        const NostrEventTags&      tags,
        const NostrEventContent&   content,
        const NostrEventSignature& sig)
    {
        this->id      = id;
        this->kind    = kind;
        this->tags    = tags;
        this->content = content;
        this->sig     = sig;
    }

    const NostrEventId& getId() const
    {
        return this->id;
    }

    const NostrEventKind& getKind() const
    {
        return this->kind;
    }

    const NostrEventTags& getTags() const
    {
        return this->tags;
    }

    const NostrEventContent& getContent() const
    {
        return this->content;
    }

    const NostrEventSignature& getSignature() const
    {
        return this->sig;
    }

   private:
    NostrEventId        id;
    NostrEventKind      kind;
    NostrEventTags      tags;
    NostrEventContent   content;
    NostrEventSignature sig;
};
}  // namespace rx_nostr

#endif  // NOSTR_EVENT_HPP
