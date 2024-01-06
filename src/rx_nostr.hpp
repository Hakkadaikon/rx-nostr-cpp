#ifndef RX_NOSTR_HPP
#define RX_NOSTR_HPP

#include "rx_nostr_interface.hpp"
#include "rx_nostr_libhv.hpp"
#include "nostr_event.hpp"
#include "logger_interface.hpp"
#include "rx_nostr_subscribe_validator.hpp"

namespace rx_nostr
{
class RxNostr final : public RxNostrInterface
{
   public:
    RxNostr(LoggerInterface* logger)
    {
        this->logger   = logger;
        this->rx_nostr = new RxNostrLibhv(logger);
    }

    ~RxNostr()
    {
        delete this->rx_nostr;
    }

    bool subscribe(
        const NostrEventCallback callback,
        const NostrEventKinds&   kinds,
        const std::string&       relay,
        const uint32_t           limit)
    {
        if (!RxNostrSubscribeValidator::validate(this->logger, callback, kinds, relay, limit)) {
            return false;
        }

        return this->rx_nostr->subscribe(callback, kinds, relay, limit);
    }

    bool unsubscribe()
    {
        return this->rx_nostr->unsubscribe();
    }

    bool setReconnectInterval(const uint32_t min_timeout, const uint32_t max_timeout)
    {
        return this->rx_nostr->setReconnectInterval(min_timeout, max_timeout);
    }

   private:
    RxNostrInterface* rx_nostr;
    LoggerInterface*  logger;
};
}  // namespace rx_nostr

#endif  // RX_NOSTR_HPP
