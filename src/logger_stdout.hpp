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
        printf("%s%s\n", this->levelToString(level), msg);
    }

    void log(const LogLevel level, const std::string msg) const
    {
        printf("%s%s\n", this->levelToString(level), msg.c_str());
    }

   private:
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
            default:
                return "[UNKNOWN] ";
        }
    }
};
}  // namespace rx_nostr

#endif  // LOGGER_STDOUT_HPP
