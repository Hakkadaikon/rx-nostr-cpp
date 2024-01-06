#ifndef RX_NOSTR_LIBHV_HPP
#define RX_NOSTR_LIBHV_HPP

#include <functional>
#include <hv/hloop.h>
#include <functional>
#include "nostr_event.hpp"
#include "rx_nostr_interface.hpp"
#include "logger_interface.hpp"
#include "hv/WebSocketClient.h"

namespace rx_nostr
{
class RxNostrLibhv final : public RxNostrInterface
{
   public:
    RxNostrLibhv(LoggerInterface* logger)
    {
        this->logger       = logger;
        this->is_connected = false;
        this->setReconnectInterval(1000, 10000);
    }

    ~RxNostrLibhv()
    {
    }

    bool subscribe(
        const NostrEventCallback callback,
        const NostrEventKinds&   kinds,
        const std::string&       relay,
        const uint32_t           limit)
    {
        this->callback = callback;

        this->ws.onopen = [this]() {
            this->onOpen();
        };

        this->ws.onmessage = [this](const std::string& msg) {
            this->onMessage(msg);
        };

        this->ws.onclose = [this]() {
            this->onClose();
        };

        // TODO: check result
        auto result = this->ws.open(relay.c_str());

        // TODO: make "unique sub_id"
        // TODO: send subscribe message
        // ws.send("[\"REQ\", \"subid\", {\"kinds\":[...], \"limit\":limit}]");

        this->is_connected = true;
        return true;
    }

    bool unsubscribe()
    {
        //TODO: send unsubscribe message
        // ws.send("[\"close\", \"subid\"]")
        //TODO: check result
        auto result        = ws.close();
        this->is_connected = false;
        return true;
    }

    bool setReconnectInterval(const uint32_t min_timeout, const uint32_t max_timeout)
    {
        if (this->is_connected) {
            this->logger->log(LogLevel::WARNING, "cannot set reconnect interval while connected");
            return false;
        }

        reconn_setting_init(&this->reconn);
        this->reconn.min_delay    = min_timeout;
        this->reconn.max_delay    = max_timeout;
        this->reconn.delay_policy = 2;
        return true;
    }

   private:
    using NostrEventSubId = std::string;
    LoggerInterface*    logger;
    NostrEventSubId     sub_id;
    hv::WebSocketClient ws;
    reconn_setting_t    reconn;
    NostrEventCallback  callback;
    bool                is_connected;

    void onOpen(void)
    {
        this->logger->log(LogLevel::INFO, "open");
    }

    void onMessage(const std::string& msg)
    {
        // TODO json -> entity
        // TODO if receive EOSE, send "ws.send("[\"close\", \"subid\"]")
        // TODO check subid
        NostrEventId      id      = NostrEventId("1");
        NostrEventKind    kind    = NostrEventKind(1);
        NostrEventTags    tags    = NostrEventTags("1", "2");
        NostrEventContent content = NostrEventContent("test content");
        NostrEventContent sig     = NostrEventContent("test sig");

        auto event = NostrEvent(id, kind, tags, content, sig);
        this->callback(event);
    }

    void onClose()
    {
        this->logger->log(LogLevel::INFO, "close");
    }
};
}  // namespace rx_nostr

#endif  // RX_NOSTR_LIBHV_HPP
