//
// Created by jason on 16/6/21.
//

#ifndef NETWORK_HTTPHANDLERCONTROLLER_H
#define NETWORK_HTTPHANDLERCONTROLLER_H

#include <unordered_map>
#include <thread>
#include "server/HttpHandler.h"
#include "HttpRequestParser.h"
#include "util/TcpSocket.h"
#include "util/EpollSet.h"

namespace myoi {
    class HttpHandlerController {
    private:
        constexpr static int THREAD_COUNT = 16;
        std::unique_ptr<HttpHandler> handlers[THREAD_COUNT]{};
        std::unique_ptr<std::thread> threads[THREAD_COUNT]{};
        const char *baseDir;


    public:
        explicit HttpHandlerController(const char *baseDir) : baseDir{baseDir} {}

        void handleConnection(TcpSocket *conn, HttpRequestParser *parser, const HttpHandler::CallBack *callback);

        void exit();
    };
}

#endif //NETWORK_HTTPHANDLERCONTROLLER_H
