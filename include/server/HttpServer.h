//
// Created by jason on 10/6/21.
//

#ifndef NETWORK_HTTPSERVER_H
#define NETWORK_HTTPSERVER_H


#include <utility>

#include "core/Ipv4Address.h"
#include "http/HttpRequestParser.h"
#include "core/Asio.h"

namespace myoi {
    constexpr size_t BUFFER_SIZE = 1024;
    constexpr size_t CONNECTION_COUNT = 64;

    struct HttpConnection {
        AsioBlock io;
        HttpRequestParser parser;
        char ioBuffer[BUFFER_SIZE];

        HttpConnection() : io{}, parser{}, ioBuffer{} {};
        ~HttpConnection() = default;
    };

    class HttpServer {
    private:
        Asio asio{};
        HttpConnection *connections[CONNECTION_COUNT]{nullptr};
        TcpSocket listener{};
        AsioBlock listenerBlock{};
        Ipv4Address hostAddress{};
        std::string baseDir{};
        AsioBlock stdinBlock{};
        char stdinBuffer[128];

        void HandleClient(HttpConnection **pConnection);
        void HandleNewConnection();
//      void HandleConsole();

        void init();

        static void logNewConnection(const TcpSocket &socket);
        static void logCloseConnection(const TcpSocket &socket);
        static void logStartServer(const TcpSocket &socket);

    public:
        HttpServer(const char *address, uint16_t port, const std::string &basedir)
            : HttpServer{Ipv4Address{address, port}, basedir} {}

        explicit HttpServer(const Ipv4Address &address, std::string basedir)
            : hostAddress{address}, baseDir{std::move(basedir)} {
            if (baseDir.back() == '/') {baseDir.pop_back();}
        }

        ~HttpServer() noexcept;

        int exec();

    };
}




#endif //NETWORK_HTTPSERVER_H
