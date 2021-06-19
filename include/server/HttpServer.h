//
// Created by jason on 16/6/21.
//

#ifndef NETWORK_HTTPSERVER_H
#define NETWORK_HTTPSERVER_H

#include "server/HttpHandlerController.h"
#include "server/LogServer.h"
#include "util/TcpSocket.h"
#include "util/EpollSet.h"
#include "HttpRequestParser.h"
#include <unordered_map>
#include <memory>
namespace myoi {

    class HttpServer {
    private:
        int terminate{1};
        Ipv4Address address{};
        TcpSocket listener{};
        EpollSet epoll{};
        LogServer log{stdout};
        std::unordered_map<int, std::unique_ptr<HttpRequestParser>> parsers{};
        std::unordered_map<int, std::unique_ptr<TcpSocket>> connections{};
        HttpHandlerController controller;

    public:

        HttpServer(const char *address, uint16_t port, const char *baseDir) : address{address, port}, controller{baseDir} {}

        int exec();

        void term();

    private:
        bool init();

        void handleListener(TcpSocket *socket);

        void handleConnection(TcpSocket *socket);

        void addConnection(const TcpSocket &socket);

        void removeConnection(TcpSocket *socket);

        HttpHandler::CallBack callback = [this](TcpSocket *socket, bool keepAlive) {
            if (keepAlive) {
                epoll.resetEvent(socket);
            } else {
                removeConnection(socket);
            }
        };


    };
}

#endif //NETWORK_HTTPSERVER_H
