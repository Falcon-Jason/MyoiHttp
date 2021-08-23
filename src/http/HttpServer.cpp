//
// Created by jason on 2021/8/23.
//

#include "http/HttpServer.h"
#include "http/HttpRequestParser.h"
#include "http/HttpHandler.h"

#include <memory>
#include <string>

namespace myoi {
    constexpr int BUFFER_SIZE = 4096;
    using HttpRequestParserPtr = std::shared_ptr<HttpRequestParser>;


    void HttpServer::onAcceptable(TcpEvent *event) {
        event->context() = HttpRequestParser{};
    }

    void HttpServer::onWritable(TcpEvent *event) {
        auto &parser = std::any_cast<HttpRequestParser &>(event->context());
        if (parser.success()) {
             HttpHandler(event, baseDir_).processWriteResponse();
        } else {
            HttpHandler(event, baseDir_).processWriteError(400);
        }
        TcpServer::removeEvent(event);
    }

    void HttpServer::onReadable(TcpEvent *event) {
        char buffer[BUFFER_SIZE];
        auto &conn = event->socket();
        auto nRead = conn.read(buffer, BUFFER_SIZE - 1);
        if (nRead <= 0) { return removeEvent(event); }

        buffer[nRead] = '\0';
        auto &parser = std::any_cast<HttpRequestParser &>(event->context());

        parser.parse(buffer);

        if (!parser.open()) {
            event->setMode(Event::Mode::WRITE);
        }
    }
}