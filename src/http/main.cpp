//
// Created by jason on 2021/8/14.
//

#include "http/HttpServer.h"

#include <memory>
#include <csignal>

std::unique_ptr<myoi::HttpServer> server;

void term(int signal) {
    server->stop();
}

int main(int argc, char **argv) {
    server = std::make_unique<myoi::HttpServer>(
            "0.0.0.0", 8080,
            std::thread::hardware_concurrency() * 2, 1024,
            "/home/jason/Documents/MyoiHttp"
    );

    signal(SIGTERM, term);

    return server->start();
}