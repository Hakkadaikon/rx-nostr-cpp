#ifndef NOSTR_EVENT_HPP
#define NOSTR_EVENT_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace rx_nostr
{
using NostrEventId        = char*;
using NostrEventPubkey    = char*;
using NostrEventKind      = int;
using NostrEventKinds     = std::vector<int>;
using NostrEventTagItem   = char*;
using NostrEventTags      = std::vector<char*>;
using NostrEventSignature = char*;
using NostrEventContent   = char*;
using NostrEventSubId     = char*;
using NostrEventCreatedAt = uint64_t;

class NostrEvent final
{
   public:
    NostrEventId        id;
    NostrEventPubkey    pubkey;
    NostrEventKind      kind;
    NostrEventTags      tags;
    NostrEventContent   content;
    NostrEventSignature sig;
    NostrEventCreatedAt created_at;
};
}  // namespace rx_nostr

#endif  // NOSTR_EVENT_HPP
