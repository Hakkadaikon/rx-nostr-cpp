#ifndef RX_NOSTR_VALIDATOR_HPP
#define RX_NOSTR_VALIDATOR_HPP

#include "logger_interface.hpp"
#include "nostr_event.hpp"
#include "rx_nostr_interface.hpp"

namespace rx_nostr
{
class RxNostrSubscribeValidator final
{
   public:
    static bool validate(
        const LoggerInterface*   logger,
        const NostrEventCallback callback,
        const NostrEventKinds&   kinds,
        const std::string&       relay,
        const uint32_t           limit)
    {
        // TODO: validate
        return true;
    }

   private:
    LoggerInterface* logger;
};
}  // namespace rx_nostr

#endif  // RX_NOSTR_VALIDATOR_HPP
