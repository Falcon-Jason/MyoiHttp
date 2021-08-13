/**
 * @file HttpProcessor.cpp
 * @author Jason Cheung
 * @date 2021.06.21
 */

#include "server/HttpProcessor.h"
#include "server/HttpHandler.h"
#include "util/FileInfo.h"
#include <fmt/format.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>

namespace myoi {
    using std::string;

    void HttpProcessor::run() {
//        fmt::print(stderr, "[INFO] Socket {} handling.\n", event->socket().index());
        switch (event_->mode()) {
            case Event::Mode::READ:
                return processRead();
            case Event::Mode::WRITE:
                return processWrite();
            default:
                return;
        }
    }

    void HttpProcessor::processRead() {
        char buffer[BUFFER_SIZE];
        auto &conn = event_->socket();
        auto nRead = conn.read(buffer, BUFFER_SIZE - 1);
        if (nRead <= 0) { return handler_->removeEvent(event_, reactor_); }

        buffer[nRead] = '\0';
        event_->parser().parse(buffer);

        if (!event_->parser().open()) {
            event_->setMode(Event::Mode::WRITE);
        }
        reactor_->resetEvent(event_);
    }

    void HttpProcessor::processWrite() {
        if (event_->parser().success()) {
            processWriteResponse();
        } else {
            processWriteError(400);
        }
        handler_->removeEvent(event_, reactor_);
//        reactor->removeEvent(event);
    }


    void HttpProcessor::processWriteResponse() {
        auto &request = event_->parser().request();
        if (request.method() == HttpMethod::POST) {
            return processWriteError(501);
        }

        HttpResponse response{};
        FileInfo file{};

        string path = handler_->baseDir() + request.uri();
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

    void HttpProcessor::processWriteError(int errCode) {
        HttpResponse response{};
        response.status_ = errCode;
        response.version_ = HttpVersion::HTTP_1_0;
        response.headers_["Close"] = "true";

        sendResponse(response);
    }

    bool HttpProcessor::sendData(const FileInfo &file) {
        int fildes = ::open(file.filename(), O_RDONLY);
        if (fildes < 0) { return false; }
        ssize_t ret = ::sendfile(event_->socket().index(), fildes, nullptr, file.size());
        ::close(fildes);
        return (ret >= 0);
    }

    bool HttpProcessor::sendResponse(const HttpResponse &response) {
        string respStr = response.toString();
        ssize_t ret = event_->socket().write(respStr.c_str(), respStr.size());
        return (ret >= 0);
    }
}