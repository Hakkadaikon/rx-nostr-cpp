#ifndef LOGGER_STDOUT_HPP
#define LOGGER_STDOUT_HPP

#include <string>
#include <cstdio>
#include <cstring>
#include "logger_interface.hpp"

namespace rx_nostr
{
class LoggerStdout final : public LoggerInterface
{
   public:
    void log(const LogLevel level, const char* msg) const
    {
        auto msg_size = strlen(msg);
        this->putsUnlocked(level, msg, msg_size);
    }

    void log(const LogLevel level, const std::string msg) const
    {
        this->putsUnlocked(level, msg.c_str(), msg.size());
    }

   private:
    void putsUnlocked(const LogLevel level, const char* msg, const size_t msg_size) const
    {
        auto level_str  = this->levelToString(level);
        auto level_size = strlen(level_str);

        for (int ii = 0; ii < level_size; ii++) {
            fputc_unlocked(level_str[ii], stdout);
        }

        for (int ii = 0; ii < msg_size; ii++) {
            fputc_unlocked(msg[ii], stdout);
        }

        fputc_unlocked('\n', stdout);
    }

    const char* levelToString(const LogLevel level) const
    {
        switch (level) {
            case LogLevel::DEBUG:
                return "[DEBUG] ";
            case LogLevel::INFO:
                return "[INFO] ";
            case LogLevel::WARNING:
                return "[WARNING] ";
            case LogLevel::ERROR:
                return "[ERROR] ";
        }
    }
};
}  // namespace rx_nostr

#endif  // LOGGER_STDOUT_HPP
