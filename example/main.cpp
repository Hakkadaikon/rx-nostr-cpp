// Sample to write received nostr event to file

//#define LOCAL
#include <rx-nostr/rx_nostr.hpp>
#include <rx-nostr/logger_interface.hpp>
#ifdef LOCAL
#include "../src/rx_nostr.hpp"
#include "../src/logger_stdout.hpp"
#else
#include <rx-nostr/rx_nostr.hpp>
#include <rx-nostr/logger_stdout.hpp>
#endif
#include <thread>
#include <cstdio>

using namespace rx_nostr;

static const int        MAX_EVENTS = 300;
static LoggerInterface* logger;
static int              count = 0;
static FILE*            fp;

void finalize()
{
    if (fp != NULL) {
        fclose(fp);
        fp = NULL;
    }

    if (logger != NULL) {
        delete logger;
        logger = NULL;
    }
}

void callback(const NostrEvent& event)
{
    if (count >= MAX_EVENTS) {
        return;
    }

    fprintf(fp,
            "\ncount[%d]\nid:[%s]\npubkey:[%s]\nkind[%d]\ncreated_at[%ld]\nsig[%s]\ncontent:\n%s\n",
            count,
            event.id,
            event.pubkey,
            event.kind,
            event.created_at,
            event.sig,
            event.content);
    count++;
}

int main(void)
{
    logger = new LoggerStdout();
    RxNostr rx_nostr(logger);

    fp = fopen("test.txt", "w");

    rx_nostr.setReconnectInterval(1000, 10000);

    logger->log(LogLevel::INFO, "[main] subscribe");
    auto ret = rx_nostr.subscribe(
        callback,
        std::vector<NostrEventKind>{1, 7},
        "wss://nos.lol/",
        //"wss://relay.nostr.wirednet.jp/",
        MAX_EVENTS);

    // limit != count
    // If you specify limit, you can get the past N events,
    // but since it is just a limit, the relay may send EOSE before the limit value is reached.
    // In this sample, instead of waiting based on the number of events received,
    // it waits for a fixed number of seconds.
    logger->log(LogLevel::INFO, "[main] Wait 3 seconds");
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // The unsubscribe command is asynchronous,
    logger->log(LogLevel::INFO, "[main] unsubscribe");
    rx_nostr.unsubscribe();

    // so it does not release resources immediately after execution, and you have to wait.
    logger->log(LogLevel::INFO, "[main] wait 2 seconds");
    sleep(2);

    logger->log(LogLevel::INFO, "[main] finalize");
    finalize();

    logger->log(LogLevel::INFO, "[main] bye");
    return 0;
}
