/**
 * @file main.cpp
 * @author Jason Cheung
 * @date 2021.04.26
 */

#include "server/HttpHandler.h"
#include "event/EventReactor.h"

#include <memory>
#include <csignal>

std::unique_ptr<myoi::HttpHandler> handler;
std::unique_ptr<myoi::EventReactor> reactor;

void term(int signal) { reactor->term(); }

int main(int argc, char **argv) {
    reactor = std::make_unique<myoi::EventReactor>();
    handler = std::make_unique<myoi::HttpHandler>("/home/jason/Documents/MyoiHttp");

    bool success = reactor->open(64);
    if (!success) { return EXIT_FAILURE; }

    success = handler->init(
            myoi::InetAddress{"127.0.0.1", 8080},
            reactor.get());
    if (!success) { return EXIT_FAILURE; }

    signal(SIGTERM, term);

    return reactor->exec();
}
