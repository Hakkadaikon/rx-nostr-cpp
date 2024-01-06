#ifndef LOGGER_INTERFACE_HPP
#define LOGGER_INTERFACE_HPP

#include <string>

namespace rx_nostr
{
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class LoggerInterface
{
   public:
    virtual ~LoggerInterface()
    {
    }
    virtual void log(const LogLevel level, const char* msg) const       = 0;
    virtual void log(const LogLevel level, const std::string msg) const = 0;
};
}  // namespace rx_nostr

#endif  // LOGGER_INTERFACE_HPP
