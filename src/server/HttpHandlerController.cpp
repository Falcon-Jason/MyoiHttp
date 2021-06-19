//
// Created by jason on 16/6/21.
//

#include "server/HttpHandlerController.h"
#include <thread>
namespace myoi {
    void HttpHandlerController::handleConnection(TcpSocket *conn, HttpRequestParser *parser, HttpHandler::CallBack callback) {
        std::thread handler{[this, conn, parser, callback](){
            auto handler = std::make_unique<HttpHandler>(baseDir);
            handler->handle(conn, parser, callback == nullptr ? [](TcpSocket *, bool) {} : callback);
        }};
        handler.detach();
    }

    void HttpHandlerController::exit() {
        // PASS
    }
}