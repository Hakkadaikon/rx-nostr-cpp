# rx-nostr-cpp  
## Summary  
rx-nostr-cpp is C++ based header only library for easy communication with Nostr relay.

## Getting Started  
You can run the example with the following command.
* meson and ninja must be installed to run make setup/make build.

```bash
cd example
make setup
make build
```

This project depends on several OSS.
When developing with rx-nostr-cpp, we recommend using the Makefile and meson configuration files (meson.build, *.wrap) provided in the sample code.

## Example  
### Print nostr event  

```cpp
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
```

## Dependency  

[libhv](https://github.com/ithewei/libhv) - C++ based websocket client  
[yyjson](https://github.com/ibireme/yyjson) - C based high performance JSON library  
[meson](https://github.com/mesonbuild/meson) - build automation software.  
[ninja](https://github.com/ninja-build/ninja) - small build system with a focus on speed.  

## Author  
Hakkadaikon

## License  
MIT
