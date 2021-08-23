//
// Created by jason on 2021/8/23.
//

#ifndef MYOI_HTTPSERVER_H
#define MYOI_HTTPSERVER_H

#include "server/TcpServer.h"
namespace myoi {

    class HttpServer : public TcpServer {
    private:
        std::string baseDir_;

    public:
        HttpServer(const char *address, uint16_t port, int threadCount,
                   int selectorQueueSize, const char *baseDir)
                : TcpServer{address, port, threadCount, selectorQueueSize}, baseDir_{baseDir} {}

        ~HttpServer() override = default;

        void onAcceptable(TcpEvent *event) override;

        void onReadable(TcpEvent *event) override;

        void onWritable(TcpEvent *event) override;

    private:

    };
}

#endif //MYOI_HTTPSERVER_H
