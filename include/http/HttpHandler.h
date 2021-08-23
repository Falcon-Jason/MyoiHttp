//
// Created by jason on 2021/8/24.
//

#ifndef MYOI_HTTPHANDLER_H
#define MYOI_HTTPHANDLER_H

#include "server/TcpEvent.h"
#include "util/FileInfo.h"

namespace myoi {
    class HttpHandler {
    private:
        TcpEvent *event;
        const std::string &baseDir;

    public:
        HttpHandler(TcpEvent *event, const std::string &baseDir)
        : event{event}, baseDir{baseDir} {}

        void processWriteResponse();

        void processWriteError(int errCode);

        bool sendData(const FileInfo &file);

        bool sendResponse(const HttpResponse &response);

    };
}

#endif //MYOI_HTTPHANDLER_H
