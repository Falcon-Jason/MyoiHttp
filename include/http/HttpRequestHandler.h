//
// Created by jason on 8/6/21.
//

#ifndef MYOI_HTTPREQUESTHANDLER_H
#define MYOI_HTTPREQUESTHANDLER_H


#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "core/TcpSocket.h"

namespace myoi {
    class HttpRequestHandler {
    private:
        HttpResponse response{};
        std::string data{};

    public:
        HttpRequestHandler() = default;

        void init(const HttpRequest &request);

        void initError(int errCode);

        bool writeTo(TcpSocket &connection);

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
