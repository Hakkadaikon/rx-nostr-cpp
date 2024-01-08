#include "../src/rx_nostr.hpp"
#include "../src/logger_stdout.hpp"
#include <thread>

using namespace rx_nostr;

static LoggerInterface* logger = new LoggerStdout();

void callback(const NostrEvent& event)
{
    logger->log(LogLevel::INFO, "------------------------------------");
    logger->log(LogLevel::INFO, "hello! callback");
    char buf[20480];
    sprintf(buf,
            "\nid:[%s]\npubkey:[%s]\nkind[%d]\ncreated_at[%ld]\nsig[%s]\ncontent:\n%s",
            event.id,
            event.pubkey,
            event.kind,
            event.created_at,
            event.sig,
            event.content);
    logger->log(LogLevel::INFO, buf);
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
        3);

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    delete logger;
}
