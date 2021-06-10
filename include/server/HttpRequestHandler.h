//
// Created by jason on 8/6/21.
//

#ifndef MYOI_HTTPREQUESTHANDLER_H
#define MYOI_HTTPREQUESTHANDLER_H


#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "core/TcpSocket.h"
#include "core/FileInfo.h"

namespace myoi {
    class HttpRequestHandler {
    private:
        HttpResponse response_{};
        FileInfo file_{};
        bool hasDataToSend_{false};

    public:
        HttpRequestHandler() = default;

        void init(const HttpRequest &request, const std::string &baseDir);

        void initError(int errCode);

        bool writeTo(const TcpSocket &connection);

        bool hasDataToSend() const { return hasDataToSend_; }

        bool sendDataTo(const TcpSocket &connection);

    private:
        const static std::map<int, std::string> StatusInfo_;

    public:
        const static char *StatusInfo(int status) {
            return StatusInfo_.count(status)
                ? StatusInfo_.at(status).c_str() : "Unknown Error";
        }
    };
}
#endif //MYOI_HTTPREQUESTHANDLER_H
