//
// Created by jason on 16/6/21.
//

#ifndef NETWORK_HTTPHANDLER_H
#define NETWORK_HTTPHANDLER_H

#include <util/FileInfo.h>
#include "HttpRequestParser.h"
#include "util/TcpSocket.h"
#include <functional>

namespace myoi {
    constexpr int BUFFER_SIZE = 1024;

    class HttpHandler {
    public:
        using CallBack = std::function<void(TcpSocket *, bool)>;

    private:
        std::string baseDir;
        char buffer[BUFFER_SIZE]{};

    public:
        explicit HttpHandler(const char *baseDir) : baseDir{baseDir} {}

        void handle(TcpSocket *connection, HttpRequestParser *parser, const CallBack* callback);

    private:

        void handleResponse(const HttpRequest *request, const TcpSocket *connection);

        void handleErrorResponse(int errCode, const TcpSocket *connection);

        bool sendData(const FileInfo& file, const TcpSocket *connection);

        bool sendResponse(const HttpResponse *response, const TcpSocket *connection);
    };
}

#endif //NETWORK_HTTPHANDLER_H
