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

myoi::HttpServer::Config config{
    .address = "127.0.0.1",
    .port = 8080,
    .queueSize = 1024,
    .threadCount = 16,
    .baseDir = "/home/myoi/web"
};

int main(int argc, char **argv) {
    server = std::make_unique<myoi::HttpServer>(config);
    signal(SIGTERM, term);
    return server->start();
}