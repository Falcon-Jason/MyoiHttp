//
// Created by jason on 26/4/21.
//

#include <unistd.h>
#include <csignal>
#include <memory>
#include <fmt/format.h>
#include "server/HttpServer.h"

using namespace myoi;

std::unique_ptr<HttpServer> server;

int main(int argc, char **argv) {
    if (argc != 4) {
        fmt::print(stderr, "[ERROR] INVALID ARGUMENTS\n");
        return EXIT_FAILURE;
    }
    server = std::make_unique<HttpServer>(
        argv[1], (uint16_t)atoi(argv[2]), argv[3]);

    signal(SIGTERM, [](int sig) { server->term(); });

    return server->exec();

//    std::function<void()> f = nullptr;
//    f();

    return 0;
}
