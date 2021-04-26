//
// Created by jason on 26/4/21.
//

#ifndef NETWORK_HTTPSERVER_H
#define NETWORK_HTTPSERVER_H

#include <string>
#include "core/TcpListener.h"
#include "core/SelectSet.h"
#include "core/Ipv4Address.h"

namespace network {
    class HttpServer {
    private:
        constexpr static int BUFFER_SIZE = 1024;
        std::string baseDir;
        TcpListener listener;
        SelectSet selectSet;
        const Ipv4Address &address;
        bool end;
        int retCode;

    public:
        HttpServer(const char *ip, int port, const char *baseDir = ".");

        int exec();

    private:
        static void HandleClient(const std::string &baseDir, TcpConnection *conn);

        static void HandleConsole(HttpServer &server);
    };
}
#endif //NETWORK_HTTPSERVER_H
