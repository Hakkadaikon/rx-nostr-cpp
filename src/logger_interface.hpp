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
    virtual void log(LogLevel level, const char* msg) = 0;
    virtual void log(LogLevel level, std::string msg) = 0;
};
}  // namespace rx_nostr

#endif  // LOGGER_INTERFACE_HPP
