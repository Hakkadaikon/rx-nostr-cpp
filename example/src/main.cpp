// Sample to write received nostr event to file

//#define LOCAL
#ifdef LOCAL
#include "../src/rx_nostr.hpp"
#include "../src/logger_stdout.hpp"
#else
#include <rx-nostr/rx_nostr.hpp>
#include <rx-nostr/logger_stdout.hpp>
#endif
#include <thread>

// rocksdb must be installed.
#include "rocksdb/db.h"

using namespace rx_nostr;

static const int        MAX_EVENTS = 300;
static LoggerInterface* logger     = nullptr;
static int              count      = 0;
static rocksdb::DB*     db         = nullptr;

void callback(const NostrEvent& event)
{
    if (count >= MAX_EVENTS) {
        return;
    }

    auto s = db->Put(rocksdb::WriteOptions(), event.id, event.content);
}

int main(void)
{
    logger = new LoggerStdout();
    RxNostr rx_nostr(logger);

    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status    = rocksdb::DB::Open(options, "./testdb", &db);
    if (!status.ok()) {
        logger->log(LogLevel::ERROR, "[main] db open error");
        return -1;
    }

    rx_nostr.setReconnectInterval(1000, 10000);

    logger->log(LogLevel::INFO, "[main] subscribe");
    auto ret = rx_nostr.subscribe(
        callback,
        std::vector<NostrEventKind>{1, 7},
        "wss://nos.lol/",
        //"wss://relay.nostr.wirednet.jp/",
        MAX_EVENTS);

    if (!ret) {
        goto FINALIZE;
    }

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
    logger->log(LogLevel::INFO, "[main] wait 3 seconds");
    std::this_thread::sleep_for(std::chrono::seconds(3));

    logger->log(LogLevel::INFO, "[main] bye");

FINALIZE:
    if (db != nullptr) {
        delete db;
    }

    if (logger != nullptr) {
        delete logger;
    }

    return 0;
}
