//
// Created by jason on 2021/8/23.
//

#ifndef MYOI_HTTPSERVER_H
#define MYOI_HTTPSERVER_H

#include "server/TcpServer.h"
namespace myoi {
    class HttpServer : public TcpServer {
    public:
        struct Config {
            const char *address;
            uint16_t port;
            int queueSize;
            int threadCount;
            const char *baseDir;

//            const static Config DEFAULT_CONFIG;
        };

    private:
        std::string baseDir_;
        HttpServer(const char *address, uint16_t port, int threadCount,
                   int queueSize, const char *baseDir)
            : TcpServer{address, port, threadCount, queueSize}, baseDir_{baseDir} {}

    public:
        explicit HttpServer(const Config &config)
            : HttpServer{config.address, config.port, config.threadCount,
                         config.queueSize, config.baseDir} {}

        ~HttpServer() override = default;

        void onAcceptable(TcpEvent *event) override;

        void onReadable(TcpEvent *event) override;

        void onWritable(TcpEvent *event) override;

    private:

    };
}

#endif //MYOI_HTTPSERVER_H
