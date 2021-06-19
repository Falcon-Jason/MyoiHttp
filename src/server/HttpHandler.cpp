//
// Created by jason on 16/6/21.
//

#include "server/HttpHandler.h"
#include "util/FileInfo.h"
#include <fmt/format.h>
#include <fcntl.h>
#include <sys/sendfile.h>

namespace myoi {
    using std::string;

    void HttpHandler::handle(TcpSocket *connection, HttpRequestParser *parser, const CallBack& callback) {
        auto n = connection->tryRead(buffer, BUFFER_SIZE - 1);
        if (n <= 0) {
            return callback(connection, false);
        }
        buffer[n] = 0;

        parser->parse(buffer);
        if (parser->success()) {
            handleResponse(&parser->request(), connection);
            return callback(connection, false);
        } else if (parser->failure()) {
            handleErrorResponse(400, connection);
            return callback(connection, false);
        }
        return callback(connection, true);
    }

    void HttpHandler::handleResponse(const HttpRequest *request, const TcpSocket *connection) {
        if (request->method() == HttpMethod::POST) {
            return handleErrorResponse(501, connection);
        }

        HttpResponse response{};
        FileInfo file{};

        string path = baseDir + request->uri();
        if (path.back() == '/') { path.append("index.html"); }
        file.setFile(path.c_str());
        if (!file.exists()) { return handleErrorResponse(404, connection); }
        if (!file.readable()) { return handleErrorResponse(403, connection); }

        response.status_ = 200;
        response.version_ = request->version();
        response.headers_["Close"] = "true";
        response.headers_["Content-length"] = fmt::format("{}", file.size());

        sendResponse(&response, connection);
        if (request->method() == HttpMethod::GET) {
            sendData(file, connection);
        }
    }

    void HttpHandler::handleErrorResponse(int errCode, const TcpSocket *connection) {
        HttpResponse response{};
        response.status_ = errCode;
        response.version_ = HttpVersion::HTTP_1_0;
        response.headers_["Close"] = "true";

        sendResponse(&response, connection);
    }

    bool HttpHandler::sendData(const FileInfo &file, const TcpSocket *connection) {
        int fildes = ::open(file.filename(), O_RDONLY);
        if (fildes < 0) { return false; }
        ssize_t ret = ::sendfile(connection->index(), fildes, nullptr, file.size());
        return (ret >= 0);
    }

    bool HttpHandler::sendResponse(const HttpResponse *response, const TcpSocket *connection) {
        string respStr = response->toString();
        ssize_t ret = connection->tryWrite(respStr.c_str(), respStr.size());
        return (ret >= 0);
    }

}