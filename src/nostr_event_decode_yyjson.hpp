#ifndef RX_NOSTR_EVENT_DECODE_YYJSON_HPP_
#define RX_NOSTR_EVENT_DECODE_YYJSON_HPP_

#include "yyjson.h"
#include "nostr_event.hpp"
#include "logger_interface.hpp"
#include "./nostr_event_decode_interface.hpp"
#include <cstring>

namespace rx_nostr
{
class NostrEventDecodeYYJSON final : public NostrEventDecodeInterface
{
   public:
    NostrEventDecodeYYJSON(LoggerInterface* logger)
        : logger(logger)
    {
    }

    bool decode(const std::string& message, NostrEventSubId& sub_id, NostrEvent& event) const
    {
        auto* doc    = yyjson_read(message.c_str(), message.size(), 0);
        auto* root   = yyjson_doc_get_root(doc);
        bool  result = true;

        // format
        // ["EVENT","sub_id",{- event data- }]

        // Check array size
        auto json_size = yyjson_arr_size(root);
        if (json_size != 3) {
            this->logger->log(LogLevel::DEBUG, std::string("invalid json size: ") + std::to_string(json_size));
            result = false;
        }

        // Check kind
        auto json_kind = yyjson_get_str(yyjson_arr_get(root, 0));
        if (strcmp(json_kind, "EVENT") != 0) {
            this->logger->log(LogLevel::DEBUG, std::string("invalid json kind: ") + json_kind);
            result = false;
        }

        // Check subscription id
        auto sub_id_str = yyjson_get_str(yyjson_arr_get(root, 1));
        if (strcmp(sub_id_str, sub_id) != 0) {
            this->logger->log(LogLevel::DEBUG,
                              std::string("invalid sub_id: ") + sub_id_str);
            result = false;
        }

        //-----------------------
        //parse event data
        //-----------------------
        // id
        auto json_data = yyjson_arr_get(root, 2);
        event.id       = (char*)getString(json_data, "id");
        if (event.id == nullptr) {
            this->logger->log(LogLevel::DEBUG, "invalid event id");
            result = false;
        }

        // pubkey
        event.pubkey = (char*)getString(json_data, "pubkey");
        if (event.pubkey == nullptr) {
            this->logger->log(LogLevel::DEBUG, "invalid event pubkey");
            result = false;
        }

        // kind
        event.kind = getNumber<NostrEventKind>(json_data, "kind");
        if (event.kind == FAILED_GET_VALUE) {
            this->logger->log(LogLevel::DEBUG, "invalid event kind");
            result = false;
        }

        // created_at
        event.created_at = getNumber<NostrEventCreatedAt>(json_data, "created_at");
        if (event.created_at == FAILED_GET_VALUE) {
            this->logger->log(LogLevel::DEBUG, "invalid event created_at");
            result = false;
        }

        // content
        event.content = (char*)getString(json_data, "content");
        if (event.content == nullptr) {
            this->logger->log(LogLevel::DEBUG, "invalid event content");
            result = false;
        }

        // sig
        event.sig = (char*)getString(json_data, "sig");
        if (event.sig == nullptr) {
            this->logger->log(LogLevel::DEBUG, "invalid event sig");
            result = false;
        }

FINALIZE:
        //TODO: parse tags
        //event.tags =
        yyjson_doc_free(doc);
        return result;
    }

   private:
    LoggerInterface* logger;
    const int        FAILED_GET_VALUE = 0;

    template <typename T>
    inline T getNumber(yyjson_val* json, const char* key) const
    {
        auto* val = yyjson_obj_get(json, key);
        if (val == nullptr) {
            return FAILED_GET_VALUE;
        }

        T conv_val;
        if (typeid(T) == typeid(NostrEventKind)) {
            conv_val = yyjson_get_int(val);
        } else if (typeid(T) == typeid(NostrEventCreatedAt)) {
            conv_val = yyjson_get_uint(val);
        } else {
            return FAILED_GET_VALUE;
        }

        if (conv_val == 0) {
            return FAILED_GET_VALUE;
        }

        return conv_val;
    }

    const char* getString(yyjson_val* json, const char* key) const
    {
        auto* val = yyjson_obj_get(json, key);
        if (val == nullptr) {
            return nullptr;
        }

        return yyjson_get_str(val);
    }
};
}  // namespace rx_nostr

#endif  // RX_NOSTR_EVENT_DECODE_YYJSON_HPP_
