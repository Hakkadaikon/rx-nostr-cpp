#ifndef RX_NOSTR_INTERFACE_HPP
#define RX_NOSTR_INTERFACE_HPP

#include <string>
#include "nostr_event.hpp"

namespace rx_nostr
{
typedef void (*NostrEventCallback)(const NostrEvent&);
class RxNostrInterface
{
   public:
    virtual ~RxNostrInterface()
    {
    }

    virtual bool setReconnectInterval(const uint32_t min_timeout, const uint32_t max_timeout) = 0;

    virtual bool subscribe(
        const NostrEventCallback callback,
        const NostrEventKinds&   kinds,
        const std::string&       relay,
        const uint32_t           limit) = 0;

    virtual bool unsubscribe() = 0;
};
}  // namespace rx_nostr

#endif  // RX_NOSTR_INTERFACE_HPP
