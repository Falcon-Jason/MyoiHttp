/**
 * @file HttpProcessor.h
 * @author Jason Cheung
 * @date 2021.06.16
 */

#ifndef MYOI_HTTPPROCESSOR_H
#define MYOI_HTTPPROCESSOR_H

#include "util/TcpSocket.h"
#include "util/FileInfo.h"
#include "event/EventReactor.h"
#include "http/HttpRequestParser.h"
#include "HttpEvent.h"
#include <functional>

namespace myoi {
    constexpr int BUFFER_SIZE = 1024;

    class HttpProcessor {
    private:
        HttpHandler *handler_;

    public:
        explicit HttpProcessor(HttpHandler *handler) : handler_{handler} {}

        void process(HttpEvent *event, EventReactor *reactor);

        void start();

        void terminate();

    private:
        void processRead(HttpEvent *event, EventReactor *reactor);

        void processWrite(HttpEvent *event, EventReactor *reactor);

        void processWriteResponse(HttpEvent *event);

        static void processWriteError(HttpEvent *event, int errCode);

        static bool sendData(HttpEvent *event, const FileInfo& file);

        static bool sendResponse(HttpEvent *event, const HttpResponse &response);
    };
}

#endif //MYOI_HTTPPROCESSOR_H
