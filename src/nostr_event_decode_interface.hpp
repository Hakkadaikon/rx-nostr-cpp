#ifndef NOSTR_EVENT_DECODE_INTERFACE_HPP
#define NOSTR_EVENT_DECODE_INTERFACE_HPP

#include "nostr_event.hpp"
#include <string>

namespace rx_nostr
{
class NostrEventDecodeInterface
{
   public:
    virtual ~NostrEventDecodeInterface()
    {
    }
    virtual bool decode(const std::string& message, NostrEventSubId& sub_id, NostrEvent& event) const = 0;
};
}  // namespace rx_nostr

#endif  // NOSTR_EVENT_DECODE_INTERFACE_HPP
