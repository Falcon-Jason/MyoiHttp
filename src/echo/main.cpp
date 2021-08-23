//
// Created by jason on 2021/8/24.
//

#include "server/TcpServer.h"

#include <memory>
#include <csignal>

namespace myoi {
    struct EchoServer : public TcpServer {
        EchoServer(const char *address, uint16_t port,
                   int threadCount, int selectorQueueSize)
                : TcpServer{address, port, threadCount, selectorQueueSize} {}

        void onReadable(TcpEvent *event) override {
            constexpr int BUFFER_SIZE = 4096;
            char buffer[BUFFER_SIZE];

            ssize_t bytes = event->socket().read(buffer, BUFFER_SIZE);
            if (bytes <= 0) { TcpServer::removeEvent(event); }
            event->socket().write(buffer, bytes);
        }
    };
}

std::unique_ptr<myoi::EchoServer> server;

void term(int signal) {
    server->stop();
}

int main(int argc, char **argv) {
    server = std::make_unique<myoi::EchoServer>(
            "0.0.0.0", 1234,
            4, 1024);

    signal(SIGTERM, term);

    return server->start();
}
