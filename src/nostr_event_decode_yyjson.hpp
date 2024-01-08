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
        auto* doc  = yyjson_read(message.c_str(), message.size(), 0);
        auto* root = yyjson_doc_get_root(doc);

        // format
        // ["EVENT","sub_id",{- event data- }]

        // Check array size
        auto json_size = yyjson_arr_size(root);
        if (json_size != 3) {
            this->logger->log(
                LogLevel::DEBUG,
                std::string("invalid json size:") + std::to_string(json_size));
            return false;
        }

        // Check kind
        auto json_kind = yyjson_get_str(yyjson_arr_get(root, 0));
        if (strcmp(json_kind, "event") != 0) {
            this->logger->log(LogLevel::DEBUG, std::string("invalid json kind:") + json_kind);
            return false;
        }

        // Check subscription id
        auto sub_id_str = yyjson_get_str(yyjson_arr_get(root, 1));
        if (strcmp(sub_id_str, sub_id.c_str()) != 0) {
            this->logger->log(LogLevel::DEBUG,
                              std::string("invalid sub_id:") + sub_id_str);
            return false;
        }

        //TODO: parse event data

        return true;
    }

   private:
    LoggerInterface* logger;
    const int        FAILED_GET_VALUE = -1;

    int getNumber(yyjson_val* json, const char* key) const
    {
        auto* val = yyjson_obj_get(json, key);
        if (val == nullptr) {
            return FAILED_GET_VALUE;
        }

        auto conv_val = yyjson_get_int(val);
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