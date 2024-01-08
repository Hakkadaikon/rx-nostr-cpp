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
using NostrEventSubId     = std::string;
using NostrEventCreatedAt = uint64_t;

class NostrEvent final
{
   public:
    NostrEventId        id;
    NostrEventKind      kind;
    NostrEventTags      tags;
    NostrEventContent   content;
    NostrEventSignature sig;
    NostrEventCreatedAt created_at;
};
}  // namespace rx_nostr

#endif  // NOSTR_EVENT_HPP
