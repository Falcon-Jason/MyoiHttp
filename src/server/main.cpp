//
// Created by jason on 2021/8/14.
//

#include "server/HttpReactor.h"

#include <memory>
#include <csignal>

std::unique_ptr<myoi::HttpReactor> reactor;

void term(int signal) {
    reactor->terminate();
}

int main(int argc, char **argv) {
    reactor = std::make_unique<myoi::HttpReactor>(
            "/home/jason/Documents/MyoiHttp",
            std::thread::hardware_concurrency() * 2);

    signal(SIGTERM, term);

    return reactor->exec();
}