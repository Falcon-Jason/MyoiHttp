//
// Created by jason on 2021/8/23.
//

#include "http/HttpServer.h"
#include "http/HttpRequestParser.h"

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
            processWriteResponse(event);
        } else {
            processWriteError(400, event);
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

    void HttpServer::processWriteResponse(TcpEvent *event) {
        auto &parser = std::any_cast<HttpRequestParser &>(event->context());
        auto &request = parser.request();
        if (request.method() == HttpMethod::POST) {
            return processWriteError(501, event);
        }

        HttpResponse response{};
        FileInfo file{};

        std::string path = baseDir_ + request.uri();
        if (path.back() == '/') { path.append("index.html"); }
        file.setFile(path.c_str());
        if (!file.exists()) { return processWriteError(404, event); }
        if (!file.readable()) { return processWriteError(403, event); }

        response.status_ = 200;
        response.version_ = request.version();
        response.headers_["Close"] = "true";
        response.headers_["Content-length"] = fmt::format("{}", file.size());

        sendResponse(response, event);
        if (request.method() == HttpMethod::GET) {
            sendData(file, event);
        }
    }

    void HttpServer::processWriteError(int errCode, TcpEvent *event) {
        HttpResponse response{};
        response.status_ = errCode;
        response.version_ = HttpVersion::HTTP_1_0;
        response.headers_["Close"] = "true";

        sendResponse(response, event);
    }

    bool HttpServer::sendData(const FileInfo &file, TcpEvent *event) {
        int fildes = ::open(file.filename(), O_RDONLY);
        if (fildes < 0) { return false; }
        ssize_t ret = ::sendfile(event->socket().index(), fildes, nullptr, file.size());
        ::close(fildes);
        return (ret >= 0);
    }

    bool HttpServer::sendResponse(const HttpResponse &response, TcpEvent *event) {
        std::string respStr = response.toString();
        ssize_t ret = event->socket().write(respStr.c_str(), respStr.size());
        return (ret >= 0);
    }
}