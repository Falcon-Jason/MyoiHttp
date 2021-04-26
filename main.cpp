//
// Created by jason on 26/4/21.
//

#include "http/HttpServer.h"
#include <fmt/format.h>
#include <cstdlib>

int main(int argc, const char **argv) {
    if (argc < 4) {
        fmt::print(stderr, "No enough argument passed\n");
        return 0;
    }
    return network::HttpServer{argv[1], atoi(argv[2]), argv[3]}.exec();
}