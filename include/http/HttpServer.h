//
// Created by jason on 2021/8/23.
//

#ifndef MYOI_HTTPSERVER_H
#define MYOI_HTTPSERVER_H

#include "server/TcpServer.h"
#include "util/FileInfo.h"

#include <fmt/format.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>

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

        [[nodiscard]] const std::string &baseDir() const { return baseDir_; }

    private:
        void processWriteResponse(TcpEvent *event);

        void processWriteError(int errCode, TcpEvent *event);

        bool sendData(const FileInfo &file, TcpEvent *event);

        bool sendResponse(const HttpResponse &response, TcpEvent *event);
    };
}

#endif //MYOI_HTTPSERVER_H
