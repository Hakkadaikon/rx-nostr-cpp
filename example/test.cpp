#include "../src/rx_nostr.hpp"
#include "../src/logger_stdout.hpp"
#include <iostream>

using namespace rx_nostr;

int main(void)
{
    LoggerInterface* logger = new LoggerStdout();
    RxNostr          rx_nostr(logger);

    delete logger;
}
