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

    void HttpProcessor::process(HttpEvent *event, EventReactor *reactor) {
//        fmt::print(stderr, "[INFO] Socket {} handling.\n", event->socket().index());
        switch (event->mode()) {
            case Event::Mode::READ:
                return processRead(event, reactor);
            case Event::Mode::WRITE:
                return processWrite(event, reactor);
            default:
                return;
        }
    }

    void HttpProcessor::processRead(HttpEvent *event, EventReactor *reactor) {
        char buffer[BUFFER_SIZE];
        auto &conn = event->socket();
        auto nRead = conn.read(buffer, BUFFER_SIZE - 1);
        if (nRead <= 0) { return handler_->removeEvent(event, reactor); }

        buffer[nRead] = '\0';
        event->parser().parse(buffer);

        if (!event->parser().open()) {
            event->setMode(Event::Mode::WRITE);
        }
        reactor->resetEvent(event);
    }

    void HttpProcessor::processWrite(HttpEvent *event, EventReactor *reactor) {
        if (event->parser().success()) {
            processWriteResponse(event);
        } else {
            processWriteError(event, 400);
        }
        handler_->removeEvent(event, reactor);
//        reactor->removeEvent(event);
    }


    void HttpProcessor::processWriteResponse(HttpEvent *event) {
        auto &request = event->parser().request();
        if (request.method() == HttpMethod::POST) {
            return processWriteError(event, 501);
        }

        HttpResponse response{};
        FileInfo file{};

        string path = handler_->baseDir() + request.uri();
        if (path.back() == '/') { path.append("index.html"); }
        file.setFile(path.c_str());
        if (!file.exists()) { return processWriteError(event, 404); }
        if (!file.readable()) { return processWriteError(event, 403); }

        response.status_ = 200;
        response.version_ = request.version();
        response.headers_["Close"] = "true";
        response.headers_["Content-length"] = fmt::format("{}", file.size());

        sendResponse(event, response);
        if (request.method() == HttpMethod::GET) {
            sendData(event, file);
        }
    }

    void HttpProcessor::processWriteError(HttpEvent *event, int errCode) {
        HttpResponse response{};
        response.status_ = errCode;
        response.version_ = HttpVersion::HTTP_1_0;
        response.headers_["Close"] = "true";

        sendResponse(event, response);
    }

    bool HttpProcessor::sendData(HttpEvent *event, const FileInfo &file) {
        int fildes = ::open(file.filename(), O_RDONLY);
        if (fildes < 0) { return false; }
        ssize_t ret = ::sendfile(event->socket().index(), fildes, nullptr, file.size());
        ::close(fildes);
        return (ret >= 0);
    }

    bool HttpProcessor::sendResponse(HttpEvent *event, const HttpResponse &response) {
        string respStr = response.toString();
        ssize_t ret = event->socket().write(respStr.c_str(), respStr.size());
        return (ret >= 0);
    }

    void HttpProcessor::start() {
        std::unique_ptr<HttpProcessor> processor{new HttpProcessor{handler_}};

        while (true) {
            handler_->queueSem_.wait();
            handler_->queueMutex_.lock();

            auto task = handler_->queue_.front();

            bool terminate = (task.reactor == nullptr || task.event == nullptr);
            if (!terminate) { handler_->queue_.pop_front(); }

            handler_->queueMutex_.unlock();

            if (terminate) {
                handler_->queueSem_.post();
                break;
            }

            auto taskEvent = dynamic_cast<HttpEvent *>(task.event);
            if (taskEvent != nullptr){
                processor->process(taskEvent, task.reactor);
            }
        }
    }


    void HttpProcessor::terminate() {
        handler_->queue_.push_front(HttpHandler::Task{nullptr, nullptr});
    }

}