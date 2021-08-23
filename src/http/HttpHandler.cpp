//
// Created by jason on 2021/8/24.
//

#include "http/HttpHandler.h"
#include "http/HttpUtil.h"

#include <fmt/format.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>


namespace myoi {
    void HttpHandler::processWriteResponse() {
        auto &parser = std::any_cast<HttpRequestParser &>(event->context());
        auto &request = parser.request();
        if (request.method() == HttpMethod::POST) {
            return processWriteError(501);
        }

        HttpResponse response{};
        FileInfo file{};

        std::string path = baseDir + request.uri();
        if (path.back() == '/') { path.append("index.html"); }
        file.setFile(path.c_str());
        if (!file.exists()) { return processWriteError(404); }
        if (!file.readable()) { return processWriteError(403); }

        response.status_ = 200;
        response.version_ = request.version();
        response.headers_["Close"] = "true";
        response.headers_["Content-length"] = fmt::format("{}", file.size());

        sendResponse(response);
        if (request.method() == HttpMethod::GET) {
            sendData(file);
        }
    }

    void HttpHandler::processWriteError(int errCode) {
        HttpResponse response{};
        response.status_ = errCode;
        response.version_ = HttpVersion::HTTP_1_0;
        response.headers_["Close"] = "true";

        sendResponse(response);
    }

    bool HttpHandler::sendData(const FileInfo &file) {
        int fildes = ::open(file.filename(), O_RDONLY);
        if (fildes < 0) { return false; }
        ssize_t ret = ::sendfile(event->socket().index(), fildes, nullptr, file.size());
        ::close(fildes);
        return (ret >= 0);
    }

    bool HttpHandler::sendResponse(const HttpResponse &response) {
        std::string respStr = response.toString();
        ssize_t ret = event->socket().write(respStr.c_str(), respStr.size());
        return (ret >= 0);
    }
}