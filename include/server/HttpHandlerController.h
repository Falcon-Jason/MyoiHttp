//
// Created by jason on 16/6/21.
//

#ifndef NETWORK_HTTPHANDLERCONTROLLER_H
#define NETWORK_HTTPHANDLERCONTROLLER_H

#include <unordered_map>
#include "server/HttpHandler.h"
#include "util/HttpRequestParser.h"
#include "util/TcpSocket.h"
#include "util/EpollSet.h"

namespace myoi {
    class HttpHandlerController {
    private:
        const char *baseDir;
    public:
        explicit HttpHandlerController(const char *baseDir) : baseDir{baseDir} {}

        void handleConnection(TcpSocket *conn, HttpRequestParser *parser, HttpHandler::CallBack callback = nullptr);

        void exit();
    };
}

#endif //NETWORK_HTTPHANDLERCONTROLLER_H
