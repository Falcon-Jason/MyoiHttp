//
// Created by jason on 26/4/21.
//

#include "server/HttpServer.h"
#include <memory>
#include <fmt/format.h>

using namespace myoi;

int main(int argc, char **argv) {
    if (argc != 4) {
        fmt::print(stderr, "[ERROR] INVALID ARGUMENTS\n");
        return EXIT_FAILURE;
    }
    std::unique_ptr<HttpServer> server{
        new HttpServer{argv[1], (uint16_t)atoi(argv[2]), argv[3]}};
    return server->exec();
}