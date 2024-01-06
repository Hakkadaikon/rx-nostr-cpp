#ifndef RX_NOSTR_LIBHV_HPP
#define RX_NOSTR_LIBHV_HPP

#include <cstdio>
//#include <format>
#include "hv/WebSocketClient.h"
#include "implode.hpp"
#include "nostr_event.hpp"
#include "rx_nostr_interface.hpp"
#include "logger_interface.hpp"

namespace rx_nostr
{
class RxNostrLibhv final : public RxNostrInterface
{
   public:
    RxNostrLibhv(LoggerInterface* logger)
    {
        this->logger       = logger;
        this->sub_id       = "";
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

        // send subscribe message
        auto cmd = this->makeSubscribeCommand(kinds, limit);
        ws.send(cmd);

        this->is_connected = true;
        return true;
    }

    bool unsubscribe()
    {
        if (!this->is_connected) {
            this->logger->log(LogLevel::WARNING, "cannot unsubscribe while not connected");
            return false;
        }

        //Send unsubscribe message
        auto cmd = this->makeUnsubscribeCommand();
        ws.send(cmd);

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

    std::string makeUnsubscribeCommand()
    {
        char cmd[128];

        std::snprintf(
            cmd,
            sizeof(cmd),
            "[\"close\", \"%s\"]",
            this->sub_id.c_str());

        return std::string(cmd);
    }

    std::string makeSubscribeCommand(const NostrEventKinds& kinds, const uint32_t limit)
    {
        // Make kinds string [1, 2, 3] -> "1, 2, 3"
        std::string kinds_str = implode(kinds.begin(), kinds.end(), ",");

        char cmd[128];

        std::snprintf(
            cmd,
            sizeof(cmd),
            "[\"REQ\", \"%s\", {\"kinds\":[%s], \"limit\":%d}]",
            this->sub_id.c_str(),
            kinds_str.c_str(),
            limit);

        return std::string(cmd);
    }

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
        NostrEventTags    tags    = NostrEventTags();
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
