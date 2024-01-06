#include "../src/rx_nostr.hpp"
#include "../src/logger_stdout.hpp"
#include <thread>

using namespace rx_nostr;

static LoggerInterface* logger = new LoggerStdout();

void callback(const NostrEvent& event)
{
    logger->log(LogLevel::INFO, "hello! callback");
}

int main(void)
{
    logger = new LoggerStdout();
    RxNostr rx_nostr(logger);

    rx_nostr.setReconnectInterval(1000, 10000);

    auto ret = rx_nostr.subscribe(
        callback,
        std::vector<NostrEventKind>{1, 7},
        "wss://nos.lol",
        100);

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    delete logger;
}
