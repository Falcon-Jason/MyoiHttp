/**
 * @file HttpProcessor.h
 * @author Jason Cheung
 * @date 2021.06.16
 */

#ifndef MYOI_HTTPPROCESSOR_H
#define MYOI_HTTPPROCESSOR_H

#include "util/TcpSocket.h"
#include "util/FileInfo.h"
#include "util/FixedThreadPool.h"
#include "event/EventReactor.h"
#include "http/HttpRequestParser.h"
#include "HttpEvent.h"
#include <functional>

namespace myoi {
    constexpr int BUFFER_SIZE = 1024;

    class HttpProcessor : public Task {
    private:
        HttpHandler *handler_;
        HttpEvent *event_;
        EventReactor *reactor_;

    public:
        explicit HttpProcessor(HttpHandler *handler, HttpEvent *event, EventReactor *reactor)
        : handler_{handler}, event_{event}, reactor_{reactor} {}

        ~HttpProcessor() override = default;

        void run() override;

    private:
        void processRead();

        void processWrite();

        void processWriteResponse();

        void processWriteError(int errCode);

        bool sendData(const FileInfo& file);

        bool sendResponse(const HttpResponse &response);
    };
}

#endif //MYOI_HTTPPROCESSOR_H
